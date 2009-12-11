/*
 *  SequenceQuery.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "SequenceQuery.h"

SequenceQuery::SequenceQuery(const string& path) {
	this->measures = shared_ptr<Measures>(new Measures(path));
	this->dimensions = shared_ptr<Dimensions>(new Dimensions(path));
	this->fragments = shared_ptr<ShellFragments>(new ShellFragments(path));
	
	this->conditions = shared_ptr<Conditions>(new Conditions());
	this->aggregations = shared_ptr<Aggregations>(new Aggregations());
	this->pattern = shared_ptr<SequenceTemplate>(new SequenceTemplate());
}

tuple< bool, string, shared_ptr<Table> > SequenceQuery::Execute() {
	vector< shared_ptr<Table> > tables;
}

Response SequenceQuery::Materialize(vector< shared_ptr<Table> >& results) {
	for(size_t i = 0; i < this->pattern->size(); i++) {
		shared_ptr<Table> table;
		table->columns->push_back("values", shared_ptr<Column>(new TListColumn<string>));		
		table->columns->push_back("records", shared_ptr<Column>(new TListColumn<RecordID>));
		
		Response materialized = this->Materialize(table);
		
		if(materialized.get<0>()) {
			Response gathered = this->GatherDimension(this->pattern->at(i)->name, "sequences", table);
			
			if(gathered.get<0>()) {
				// prepend all the strings in the sequences column with this alias
				shared_ptr< TListColumn<string> > sequences = 
				static_pointer_cast< TListColumn<string> >(table->columns->at("sequences"));
				
				size_t size = sequences->size();
				for(size_t i = 0; i < size; i++ ) {
					
					size_t csize = sequences->at(i).size();
					for(size_t j = 0; j < csize; j++) {
						sequences->at(i).at(j).insert(0, this->pattern->at(i)->alias + "-");
					}
				}
				
				results.push_back(table);
			}
		} else {
			return materialized;
		}
	}
	
	return make_tuple(ok, success);
}

Response SequenceQuery::Materialize(shared_ptr<Table> results) {
	vector<string> inquire;
	vector<string> dimensions;
	map<string, string> instantiate;
	Conditions inquiry_conditions;
	
	// Go through and find all the dimensions we need to inquire
	
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition> condition = this->conditions->at(i);
		
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
	
	this->Construct(inquired, dimensions, results);
	
	return make_tuple(ok, success);	
}

Response SequenceQuery::Merge(vector< shared_ptr<Table> >& tables, shared_ptr<Table> results) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Match(shared_ptr<Table> results) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Aggregate(shared_ptr<Table> results) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Sweep(shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

/*
 * All sorts of gathering
 */ 

Response SequenceQuery::GatherMeasure(const string& measure, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

Response SequenceQuery::GatherMeasure(const string& measure, const string& alias, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

Response SequenceQuery::GatherMeasures(const set<string>& measures, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

Response SequenceQuery::GatherDimension(const string& dimension, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

Response SequenceQuery::GatherDimension(const string& dimension, const string& alias, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

Response SequenceQuery::GatherDimensions(const set<string>& dimension, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

void SequenceQuery::Construct(Inquired& inquired, vector<string>& dimensions, shared_ptr<Table> results) {
	vector<string> values;
	vector<RecordID> records;
	this->Construct(inquired, dimensions, 0, values, records, results);
}

void SequenceQuery::Construct(Inquired& inquired, vector<string>& dimensions, 
											int offset, vector<string>& values, vector<RecordID>& records, shared_ptr<Table> results) {
	
	if(dimensions.size() == offset) {
		shared_ptr< TListColumn<string> > values_column = 
		static_pointer_cast< TListColumn<string> >(results->columns->at("values"));
		shared_ptr< TListColumn<RecordID> > records_column = 
		static_pointer_cast< TListColumn<RecordID> >(results->columns->at("records"));

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
	}
}
