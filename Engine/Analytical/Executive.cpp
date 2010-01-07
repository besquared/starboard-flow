/*
 *  Executive.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Executive.h"

using namespace Flow::Engine;

Analytical::Executive::Executive(Domain::Base* domain, Query* query) {
	this->domain = domain;
	this->query = query;
}

bool Analytical::Executive::Execute(Groups& results) {
	if(!this->Materialize(results)) return false;
	if(!this->Aggregate(results)) return false;
	if(!this->Sweep(results)) return false;
	return true;
}

bool Analytical::Executive::Materialize(Groups& results) {
	map<string, string> instantiate;
	this->query->Instantiate(instantiate);
	
	RIDList instantiated;
	if(instantiate.size() > 0) {
		this->domain->indices->Lookup(instantiate, instantiated);
		if(instantiated.size() == 0) return true;
	}
	
	set<string> inquire;
	Conditions conditions;
	this->query->Inquire(inquire, conditions);
	
	vector<string> inquired_dims;
	vector<string> instantiated_dims;
	this->query->Dimensions(instantiated_dims, inquired_dims);
	
	if(inquire.size() > 0) {
		RIDTree inquired;
		this->domain->indices->Lookup(inquire, conditions, inquired);
		
		this->Construct(instantiated_dims, instantiated, inquired_dims, inquired, results);
	} else {
		if(instantiated.size() > 0) {
			vector<string> values;
			for(size_t i = 0; i < instantiated_dims.size(); i++) {
				results.dimensions.push_back(instantiated_dims[i]);
				values.push_back(instantiate[instantiated_dims[i]]);
			}
			
			Group group(values);
			results.push_back(group);
			copy(instantiated.begin(), instantiated.end(), back_inserter(results.back()));
			
			// just insert the instantiated ids into groups
		}
	}
	
	return true;
}

bool Analytical::Executive::Aggregate(Groups& base) {
	// go through all the aggregations and gather
	//   their measures from disk if we don't have them
	
	//	size_t size = this->aggregates->size();
	//	
	//	set<string> measures;
	//	for(size_t i = 0; i < size; i++) {
	//		vector<string> ameasures = this->aggregates->at(i)->measures;
	//		measures.insert(ameasures.begin(), ameasures.end());
	//	}
	//	
	//	if(this->Gather(measures, base)) {
	//		for(size_t j = 0; j < size; j++) {
	//			this->aggregates->at(j)->Apply(base);	
	//		}
	//		return true;
	//	} else {
	//		return false;
	//	}
	return true;
}

bool Analytical::Executive::Sweep(Groups& base) {
	// go through and drop the columns that 
	//  we don't want returned (records and measures)
	
	//	size_t size = this->aggregates->size();
	//	
	//	set<string> measures;
	//	for(size_t i = 0; i < size; i++) {
	//		vector<string> ameasures = this->aggregates->at(i)->measures;
	//		measures.insert(ameasures.begin(), ameasures.end());
	//	}
	//	measures.insert("records");
	//	
	//	set<string>::iterator measure;
	//	for(measure = measures.begin(); measure != measures.end(); measure++) {
	//		base.erase(*measure);
	//	}
	//	
	return true;
}

// Gather all the measures needed by the aggregates
bool Analytical::Executive::Gather(const set<string>& measures, Groups& base) {
	//	set<string>::const_iterator measure;
	//	for(measure = measures.begin(); measure != measures.end(); measure++) {		
	//		shared_ptr< Column::TListColumn<double> > values(new Column::TListColumn<double>(*measure));
	//		
	//		shared_ptr< Column::TColumn<RIDList> > records = 
	//		static_pointer_cast< Column::TColumn<RIDList> >(base.at("records"));
	//		
	//		vector<double> mvalues;
	//		for(size_t i = 0; i < records->size(); i++) {
	//			mvalues.clear();
	//			this->domain->measures->Lookup(*measure, records->at(i), mvalues);
	//			values->push_back(mvalues);
	//		}			
	//		base.push_back(static_pointer_cast<Column::Base>(values));
	//	}
	
	return true;
}

/*
 * Construction
 */
void Analytical::Executive::Construct(vector<string>& instantiated_dims, RIDList& instantiated, 
																			vector<string>& inquired_dims, RIDTree& inquired, Groups& results) {
	RIDList records;
	vector<string> values;
	this->Construct(instantiated_dims, instantiated, 
									inquired_dims, inquired, 0, values, records, results);
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
void Analytical::Executive::Construct(vector<string>& instantiated_dims, RIDList& instantiated, 
																			vector<string>& inquired_dims, RIDTree& inquired, int offset, 
																			vector<string>& values, RIDList& records, Groups& results) {
	
	if(inquired_dims.size() == offset) {
		RIDList intersected = records & instantiated;
		
		if(intersected.size() > 0) {
			Group group(values);
			results.push_back(group);
			copy(results.back().begin(), results.back().end(), back_inserter(results.back()));
		}
		return;
	}
	
	RIDMap::iterator rpair;
	RIDMap rmap = inquired[inquired_dims[offset]];
	for(rpair = rmap.begin(); rpair != rmap.end(); rpair++) {
		RIDList intersection = 
		(records.empty() ? rpair->second : records & rpair->second);
		
		if(intersection.size() > 0) {
			values.push_back(rpair->first);
			this->Construct(instantiated_dims, instantiated, inquired_dims, 
											inquired, offset + 1, values, intersection, results);
			values.pop_back();
		}
	}
}