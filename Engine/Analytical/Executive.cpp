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
	query->Instantiate(instantiate);
	
	RIDList instantiated;
	if(instantiate.size() > 0) {
		domain->indices->Lookup(instantiate, instantiated);
		if(instantiated.size() == 0) return true;
	}
	
	set<string> inquire;
	Conditions conditions;
	query->Inquire(inquire, conditions);
	
	vector<string> inquired_dims;
	vector<string> instantiated_dims;
	query->Dimensions(instantiated_dims, inquired_dims);
	
	vector<string> instantiated_vals;
	query->InstantiatedValues(instantiated_vals);
	
	if(inquire.size() > 0) {
		results.dimensions.insert(results.dimensions.end(), inquired_dims.begin(), inquired_dims.end());
		results.dimensions.insert(results.dimensions.end(), instantiated_dims.begin(), instantiated_dims.end());
		
		RIDTree inquired;
		domain->indices->Lookup(inquire, conditions, inquired);
		this->Construct(instantiated_vals, instantiated, inquired_dims, inquired, results);
	} else {
		if(instantiated.size() > 0) {
			vector<string> values;
			for(size_t i = 0; i < instantiated_dims.size(); i++) {
				results.dimensions.push_back(instantiated_dims[i]);
				values.push_back(instantiate[instantiated_dims[i]]);
			}
			
			Group group(values);
			results.push_back(group);
			results.back().insert(results.back().end(), instantiated.begin(), instantiated.end());
		}
	}
	
	return true;
}

bool Analytical::Executive::Aggregate(Groups& base) {	
	set<string> measures;
	query->Measures(measures);
	this->Gather(measures, base);
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(base);
	}
	
	return true;
}

// Gather all the measures needed by the aggregates
bool Analytical::Executive::Gather(const set<string>& measures, Groups& base) {
	// Make this multithreaded
	Groups::iterator group;
	set<string>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		for(group = base.begin(); group != base.end(); group++) {
			if(*measure != "records") {
				domain->measures->Lookup(*measure, *group, group->measures(*measure));
			}
		}
	}
	
	return true;
}

bool Analytical::Executive::Sweep(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		group->clear();
		group->clear_measures();
	}
	
	return true;
}

/*
 * Construction
 */
void Analytical::Executive::Construct(vector<string>& instantiated_vals, RIDList& instantiated, 
																			vector<string>& inquired_dims, RIDTree& inquired, Groups& results) {
	RIDList records;
	vector<string> values;
	this->Construct(instantiated_vals, instantiated, 
									inquired_dims, inquired, 0, values, records, results);
}

/*
 Takes a set of inquired dimensions such as:
 {A => {a1 => [1, 2, 3]}, B => {b1 => [1, 2], b2 => [3]}}
 
 and builds a table with dimension values corresponding record list
 +----------+--------+
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
void Analytical::Executive::Construct(vector<string>& instantiated_vals, RIDList& instantiated, 
																			vector<string>& inquired_dims, RIDTree& inquired, int offset, 
																			vector<string>& values, RIDList& records, Groups& results) {
	
	if(inquired_dims.size() == offset) {
		RIDList intersected = records & instantiated;
		
		if(intersected.size() > 0) {
			results.push_back(Group(values));
			results.back().insert(results.back().end(), intersected.begin(), intersected.end());
			results.back().values.insert(results.back().values.end(), instantiated_vals.begin(), instantiated_vals.end());
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
			this->Construct(instantiated_vals, instantiated, inquired_dims, 
											inquired, offset + 1, values, intersection, results);
			values.pop_back();
		}
	}
}