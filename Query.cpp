/*
 *  Query.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * A query takes a measure and a set of conditions in the form of
 *  {"A" => "a1", "B" => "?", "C" => "*"}
 *
 * and returns a set of column vectors that contains the appropriate answers, 
 * for instance a query like 
 * 
 * {"Product" => "P1", "Store" => "?" : SUM(SALE), COUNT(SALE)} 
 *
 * might return
 *
 * [ [S1, S2, S3], [10.5, 10.8, 10.2], [2, 2, 2] ]
 */

#include "Query.h"

Query::Query(ShellFragments* fragments, Measures* measures) {
	this->fragments = fragments;
	this->measures = measures;
	this->conditions = new Conditions();
	this->aggregations = new vector< shared_ptr<Aggregation> >;
}

tuple< bool, string, shared_ptr<Table> > Query::Execute() {
	shared_ptr<Table> table(new Table);
	
	shared_ptr<Column> column(new TListColumn<string>);
	shared_ptr<Column> records(new TListColumn<RecordID>);
	table->columns->push_back("values", column);		
	table->columns->push_back("records", records);
	
	Response materialized = this->Materialize(table);
	Response aggregated = this->Aggregate(table);
	Response swept = this->Sweep(table);
	
	if(aggregated.get<0>()) {
		return make_tuple(ok, success, table);
	} else {
		return make_tuple(error, aggregated.get<1>(), table);
	}
}

Response Query::Materialize(shared_ptr<Table> table) {
	vector<string> inquire;
	vector<string> dimensions;
	map<string, string> instantiate;
	Conditions inquiry_conditions;
	
	Conditions* conditions = this->conditions;
	for(size_t i = 0; i < conditions->size(); i++) {
		shared_ptr<Condition> condition = conditions->at(i);
		
		switch(condition->type) {
			case Condition::EQ : {
				shared_ptr<EQ> equals = static_pointer_cast<EQ>(condition);
				
				if(equals->value == "?") {
					inquire.push_back(condition->column);
				} else {
					instantiate[condition->column] = equals->value;
				}
				break;
			}
			
			default : {
				inquiry_conditions.push_back(condition->column, condition);
				break;
			}
		}
		
		dimensions.push_back(condition->column);
	}
	
	Inquired inquired;
	this->fragments->Lookup(instantiate, inquire, inquiry_conditions, inquired);

	this->Construct(inquired, dimensions, table);
	
	return make_tuple(ok, success);
}

// Gather all the measures needed by the aggregates
Response Query::Gather(const set<string>& measures, shared_ptr<Table> base) {
	set<string>::iterator iter;
	for(iter = measures.begin(); iter != measures.end(); iter++) {
		string measure = *iter;
		
		if(base->columns->exist(measure)) {
			continue;
		}
		
		shared_ptr< TListColumn<double> > values(new TListColumn<double>);
		
		tuple< bool, string, shared_ptr<Measure> > opened = this->measures->OpenReader(measure);
		
		if(opened.get<0>()) {
			shared_ptr<Measure> database = opened.get<2>();
			
			shared_ptr< TListColumn<RecordID> > records = 
			static_pointer_cast< TListColumn<RecordID> >(base->columns->at("records"));
			
			vector<double> mvalues;
			for(size_t i = 0; i < records->size(); i++) {
				mvalues.clear();
				database->Get(records->at(i), mvalues);
				values->push_back(mvalues);
			}
			
			shared_ptr<Column> avalues = static_pointer_cast<Column>(values);
			base->columns->push_back(measure, avalues);
		} else {
			return make_tuple(error, opened.get<1>());
		}
	}
	
	return make_tuple(ok, success);
}

Response Query::Aggregate(shared_ptr<Table> base) {
	// go through all the aggregations and gather
	//   their measures from disk if we don't have them
	size_t size = this->aggregations->size();
	
	set<string> measures;
	for(size_t i = 0; i < size; i++) {
		vector<string> ameasures = this->aggregations->at(i)->measures;
		measures.insert(ameasures.begin(), ameasures.end());
	}
	
	Response gathered = this->Gather(measures, base);
	
	if(gathered.get<0>()) {
		for(size_t j = 0; j < size; j++) {
			this->aggregations->at(j)->Apply(base);	
		}
		return make_tuple(ok, success);
	} else {
		return gathered;
	}
}

Response Query::Sweep(shared_ptr<Table> base) {
	// go through and drop the columns that 
	//  we don't want returned (records and measures)
	
	size_t size = this->aggregations->size();
	
	set<string> measures;
	for(size_t i = 0; i < size; i++) {
		vector<string> ameasures = this->aggregations->at(i)->measures;
		measures.insert(ameasures.begin(), ameasures.end());
	}
	measures.insert("records");
	
	set<string>::iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		base->columns->erase(*measure);
	}
	
	return make_tuple(ok, success);
}

/*
 * Construction
 */

void Query::Construct(Inquired& inquired, vector<string>& dimensions, shared_ptr<Table> results) {
	vector<string> values;
	vector<RecordID> records;
	this->Construct(inquired, dimensions, 0, values, records, results);
}

/*
 Takes a set of inquired dimensions such as:
	{A => {a1 => [1, 2, 3]}, B => {b1 => [1, 2], b2 => [3]}}
 
 and builds a table with dimension values corresponding record list
 +----+-----+--------+
 | values   | id     |
 |----------|--------|
 | [a1, b1] | [1, 2] |
 | [a1, b2] | [3]    |
 +----------+--------|
 
 values holds the list of dimension values, ie: a1, b1
 records hold the list of records for those values, ie: [1, 2]
 
 We do this by a depth first search, building nodes as we traverse
 down "branches". First we start with A:a1, descend into B and intersect
 list A:a1 with B:b1, if there are any members of this new list, we descend
 again and the termination condition triggers and we copy the values list
 and the id list into the table and return. We continue by searching B:b2
 and so on.
*/
void Query::Construct(Inquired& inquired, vector<string>& dimensions, 
	int offset, vector<string>& values, vector<RecordID>& records, shared_ptr<Table> results) {
	
	if(dimensions.size() == offset) {
		// offsets and limits for later
		// if(iteration >= loffset) return;

		shared_ptr< TListColumn<string> > values_column = 
			static_pointer_cast< TListColumn<string> >(results->columns->at("values"));
		shared_ptr< TListColumn<RecordID> > records_column = 
			static_pointer_cast< TListColumn<RecordID> >(results->columns->at("records"));
		
		// cout << "Pushing back " << Common::Inspect(values) << 
		//		" => " << Common::Inspect(records)  <<  endl;

		values_column->push_back(values);
		records_column->push_back(records);

		return;
	}
	
	InquiredDimension::iterator iter;
	InquiredDimension dimension = inquired[dimensions[offset]];

	for(iter = dimension.begin(); iter != dimension.end(); iter++) {		
		vector<RecordID> intersection;

		if(records.size() == 0) {
			intersection = iter->second;
		} else {
			intersection = Common::Intersect(records, iter->second);
		}
		
		if(intersection.size() > 0) {
			values.push_back(iter->first);
			this->Construct(inquired, dimensions, offset + 1, values, intersection, results);
			values.pop_back();
		}
		
		// offsets and limits for later
		// if(table->size() > limit) break;
	}
}