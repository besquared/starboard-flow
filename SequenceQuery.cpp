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
	shared_ptr<Table> table;
	vector< shared_ptr<Table> > tables;
	
	Response materialized = this->Materialize(tables);
	
	if(!materialized.get<0>()) {
		return make_tuple(error, materialized.get<1>(), table);
	}
	
	Response merged = this->Merge(tables, table);
	
	if(!merged.get<0>()) {
		return make_tuple(error, materialized.get<1>(), table);
	}
	
	return make_tuple(ok, success, table);
}

Response SequenceQuery::Materialize(vector< shared_ptr<Table> >& results) {
	Response materialized;
	
	for(size_t i = 0; i < this->pattern->size(); i++) {
		shared_ptr<SequenceDimension> pattern = this->pattern->at(i);
		
		shared_ptr<Table> table;
		shared_ptr<Column> key(new TColumn<SequenceKey>);
		shared_ptr<Column> events(new TListColumn<SequenceEvent>);
		
		table->columns->push_back("key", key);		
		table->columns->push_back("events", events);
		
		materialized = this->Materialize(table);
		
		if(materialized.get<0>()) {
			materialized = this->Materialize(events, pattern->name, pattern->alias);
			
			if(materialized.get<0>()) {
				return make_tuple(ok,success);
			} else {
				return materialized;
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

Response SequenceQuery::Materialize(shared_ptr< Column > column, const string& dimension, const string& alias) {
	shared_ptr< TListColumn<SequenceEvent> > base = 
		static_pointer_cast< TListColumn<SequenceEvent> >(column);
	
	tuple< bool, string, shared_ptr<Dimension> > opened = this->dimensions->OpenReader(dimension);
	
	if(opened.get<0>()) {
		shared_ptr<Dimension> database = opened.get<2>();
		
		size_t i, j, evsize;
		vector<RecordID> keys;
		map<RecordID, string> values;
		vector<SequenceEvent> events;
		
		// Scan the column to collect all records
		for(i = 0; i < base->size(); i++) {
			events = base->at(i);
			evsize = events.size();
			for(j = 0; j < evsize; j++) {
				keys.push_back(events[j].record);
			}
		}
		
		// Fetch all the dimension values at once
		database->Get(keys, values);
		
		// Assign each sequence event the proper value
		for(i = 0; i < base->size(); i++) {
			events = base->at(i);
			evsize = events.size();
			for(j = 0; j < evsize; j++) {
				events[j].alias = alias;
				events[j].value = values[events[j].record];
			}
		}
		
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, opened.get<1>());
	}	
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

/*
 * Construction
 */
void SequenceQuery::Construct(Inquired& inquired, vector<string>& dimensions, shared_ptr<Table> results) {
	vector<string> values;
	vector<RecordID> records;
	this->Construct(inquired, dimensions, 0, values, records, results);
}

void SequenceQuery::Construct(Inquired& inquired, vector<string>& dimensions, 
											int offset, vector<string>& values, vector<RecordID>& records, shared_ptr<Table> results) {
	
	if(dimensions.size() == offset) {
		shared_ptr< TColumn<SequenceKey> > values_column = 
		static_pointer_cast< TColumn<SequenceKey> >(results->columns->at("key"));
		shared_ptr< TListColumn<SequenceEvent> > events_column = 
		static_pointer_cast< TListColumn<SequenceEvent> >(results->columns->at("events"));

		values_column->push_back(SequenceKey(values));
		
		vector<SequenceEvent> events;
		for(int i = 0; i < records.size(); i++) {
			events.push_back(SequenceEvent(records[i]));
		}
		
		events_column->push_back(events);
		
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
