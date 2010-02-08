/*
 *  Constructor.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Constructor.h"

using namespace Flow::Engine;

bool Pipeline::Constructor::Execute(Domain::Base* domain, Query::Base* query, vector<WorkSet>& worksets) {
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
	
	if(inquire.size() > 0) {    		
		RIDTree inquired;
		domain->indices->Lookup(inquire, conditions, inquired);
		Construct(instantiate, instantiated, inquired_dims, inquired, worksets);
    cout << "Finished construction" << endl;
	} else {
		if(instantiated.size() > 0) {
			worksets.push_back(WorkSet(instantiate, instantiated));
		}
	}
	
	return true;
}

/*
 * Construction
 */
void Pipeline::Constructor::Construct(map<string, string>& instantiate, RIDList& instantiated, 
                                      vector<string>& inquired_dims, RIDTree& inquired, vector<WorkSet>& worksets) {
	RIDList records;
	map<string, string> values;
	Construct(instantiate, instantiated, 
            inquired_dims, inquired, 0, values, records, worksets);
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
void Pipeline::Constructor::Construct(map<string, string>& instantiate, RIDList& instantiated, 
																			 vector<string>& inquired_dims, RIDTree& inquired, size_t offset, 
																			 map<string, string>& values, RIDList& records, vector<WorkSet>& worksets) {
	
	if(inquired_dims.size() == offset) {
		RIDList intersected = records & instantiated;
		
		if(intersected.size() > 0) {
      map<string, string> group_values;
      group_values.insert(values.begin(), values.end());
      group_values.insert(instantiate.begin(), instantiate.end());
      worksets.push_back(WorkSet(group_values, intersected));
      cout << "Added workset to list of results" << endl;
		}
    
		return;
	}
	
  string& dimension = inquired_dims[offset];
  
  cout << "Intersecting potential groups with dimension " << dimension << endl;
  
  RIDMap::iterator rpair;
	RIDMap rmap = inquired[dimension];
	for(rpair = rmap.begin(); rpair != rmap.end(); rpair++) {
    cout << "Intersecting with values " << rpair->first << endl;
		RIDList intersection = 
		(records.empty() ? rpair->second : records & rpair->second);
		
		if(intersection.size() > 0) {
      values[dimension] = rpair->first;
			Construct(instantiate, instantiated, inquired_dims, 
								inquired, offset + 1, values, intersection, worksets);
      cout << "Where do we break damnit?" << endl;
      values.erase(dimension);
      cout << "What about here?" << endl;
		}
	}
}