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
		table->columns->push_back("sequences", shared_ptr<Column>(new TListColumn<string>));
		
		Response materialized = this->Materialize(table);
		
		if(materialized.get<0>()) {
			results.push_back(table);
		} else {
			return materialized;
		}
	}
	
	return make_tuple(ok, success);
}

Response SequenceQuery::Materialize(shared_ptr<Table> results) {
//	vector<string> inquire;
//	vector<string> dimensions;
//	map<string, string> instantiate;
//	Conditions inquiry_conditions;
//	
//	Conditions* conditions = this->conditions;
//	for(size_t i = 0; i < conditions->size(); i++) {
//		shared_ptr<Condition> condition = conditions->at(i);
//		
//		switch(condition->type) {
//			case Condition::EQ : {
//				shared_ptr<EQ> equals = static_pointer_cast<EQ>(condition);
//				
//				if(equals->value == "?") {
//					inquire.push_back(condition->column);
//				} else {
//					instantiate[condition->column] = equals->value;
//				}
//				break;
//			}
//				
//			default : {
//				inquiry_conditions.push_back(condition->column, condition);
//				break;
//			}
//		}
//		
//		dimensions.push_back(condition->column);
//	}
//	
//	Inquired inquired;
//	this->fragments->Lookup(instantiate, inquire, inquiry_conditions, inquired);
//	
//	this->Construct(inquired, dimensions, table);
	
	return make_tuple(ok, success);	
}

Response SequenceQuery::Merge(vector< shared_ptr<Table> >& tables, shared_ptr<Table> results) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Match(shared_ptr<Table> results) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Gather(const set<string>& measures, shared_ptr<Table> base) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Aggregate(shared_ptr<Table> results) {
	return make_tuple(ok, success);
}

Response SequenceQuery::Sweep(shared_ptr<Table> base) {
	return make_tuple(ok, success);
}
