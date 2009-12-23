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

Analytical::Query::Query(Domain::Base* domain) {
	this->domain = domain;
	this->conditions = new Conditions();
	this->aggregates = new Aggregates();
}

bool Analytical::Query::Execute(Table& results) {
	shared_ptr<Column::Base> values(new Column::TListColumn<string>("values"));
	shared_ptr<Column::Base> records(new Column::TListColumn<RecordID>("records"));
	results.push_back(values);		
	results.push_back(records);
	
	if(!this->Materialize(results)) { return false; }
	if(!this->Aggregate(results)) { return false; }
	if(!this->Sweep(results)) { return false; }
	return true;
}

bool Analytical::Query::Materialize(Table& table) {
	set<string> inquire;
	vector<string> dimensions;
	map<string, string> instantiate;
	Conditions inquiry_conditions;
	
	Conditions* conditions = this->conditions;
	for(size_t i = 0; i < conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = conditions->at(i);
		
		switch(condition->type) {
			case Condition::Base::EQ : {
				shared_ptr<Condition::Eq> equals = static_pointer_cast<Condition::Eq>(condition);
				
				if(equals->value == "?") {
					inquire.insert(condition->column);
				} else {
					instantiate[condition->column] = equals->value;
				}
				break;
			}
			
			default : {
				inquiry_conditions.push_back(condition);
				break;
			}
		}
		
		dimensions.push_back(condition->column);
	}
	
	RIDTree inquired;
	this->domain->indices->Lookup(inquire, inquiry_conditions, inquired);
	this->Construct(inquired, dimensions, table);
	return true;
}

// Gather all the measures needed by the aggregates
bool Analytical::Query::Gather(const set<string>& measures, Table& base) {
	set<string>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
//		if(base->columns->exist(*measure)) { continue; }
		
		shared_ptr< Column::TListColumn<double> > values(new Column::TListColumn<double>(*measure));
		
		shared_ptr< Column::TColumn<RIDList> > records = 
		static_pointer_cast< Column::TColumn<RIDList> >(base.at("records"));
		
		vector<double> mvalues;
		for(size_t i = 0; i < records->size(); i++) {
			mvalues.clear();
			this->domain->measures->Lookup(*measure, records->at(i), mvalues);
			values->push_back(mvalues);
		}			
		base.push_back(static_pointer_cast<Column::Base>(values));
	}
	
	return true;
}

bool Analytical::Query::Aggregate(Table& base) {
	// go through all the aggregations and gather
	//   their measures from disk if we don't have them
	size_t size = this->aggregates->size();
	
	set<string> measures;
	for(size_t i = 0; i < size; i++) {
		vector<string> ameasures = this->aggregates->at(i)->measures;
		measures.insert(ameasures.begin(), ameasures.end());
	}
	
	if(this->Gather(measures, base)) {
		for(size_t j = 0; j < size; j++) {
			this->aggregates->at(j)->Apply(base);	
		}
		return true;
	} else {
		return false;
	}
}

bool Analytical::Query::Sweep(Table& base) {
	// go through and drop the columns that 
	//  we don't want returned (records and measures)
	
	size_t size = this->aggregates->size();
	
	set<string> measures;
	for(size_t i = 0; i < size; i++) {
		vector<string> ameasures = this->aggregates->at(i)->measures;
		measures.insert(ameasures.begin(), ameasures.end());
	}
	measures.insert("records");
	
	set<string>::iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		base.erase(*measure);
	}
	
	return true;
}

/*
 * Construction
 */
void Analytical::Query::Construct(RIDTree& inquired, vector<string>& dimensions, Table& results) {
	vector<string> values;
	RIDList records;
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
void Analytical::Query::Construct(RIDTree& inquired, vector<string>& dimensions, 
																	int offset, vector<string>& values, RIDList& records, Table& results) {
	
	if(dimensions.size() == offset) {
		shared_ptr< Column::TListColumn<string> > values_column = 
			static_pointer_cast< Column::TListColumn<string> >(results.at("values"));
		shared_ptr< Column::TColumn<RIDList> > records_column = 
			static_pointer_cast< Column::TColumn<RIDList> >(results.at("records"));

		values_column->push_back(values);
		records_column->push_back(records);

		return;
	}
	
	RIDMap::iterator rpair;
	RIDMap rmap = inquired[dimensions[offset]];

	for(rpair = rmap.begin(); rpair != rmap.end(); rpair++) {		
		RIDList intersection;
		if(records.size() == 0) {
			intersection = rpair->second;
		} else {
			intersection = records & rpair->second;
		}
		
		if(intersection.size() > 0) {
			values.push_back(rpair->first);
			this->Construct(inquired, dimensions, offset + 1, values, intersection, results);
			values.pop_back();
		}
	}
}