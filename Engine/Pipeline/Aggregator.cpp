/*
 *  Aggregator.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregator.h"

bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Analytical* query, vector<WorkSet>& worksets) {
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(worksets);
	}
	
	return true;
}

// Iterate over matches, aggregate them, put those into new groups
bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Sequential* query, 
                                   vector<WorkSet>& worksets, MatchSet& matchset, ResultSet& resultset) {
  
  vector<string> grpdims = query->sequence_group_by;
  set<string> ptndims = query->pattern.dimensions();
  set<string> agtdims = query->aggregates->aliases();
  
  resultset.columns.insert(resultset.columns.end(), grpdims.begin(), grpdims.end());
  resultset.columns.insert(resultset.columns.end(), ptndims.begin(), ptndims.end());
  resultset.columns.insert(resultset.columns.end(), agtdims.begin(), agtdims.end());
	
  // WE HAVE ZE MATCHSET
  map<string, Value> row;
  vector<size_t>::iterator key;
  for(key = matchset.keys.begin(); key != matchset.keys.end(); key++) {
    Matching& matching = matchset[*key];
    
    vector<string>::iterator groupval;
    for(groupval = grpdims.begin(); groupval != grpdims.end(); groupval++) {
      row[*groupval] = matching.values[*groupval];
    }
    
    set<string>::iterator ptnval;
    for(ptnval = ptndims.begin(); ptnval != ptndims.end(); ptnval++) {
      row[*ptnval] = matching.values[*ptnval];
    }
    
    // make row here with matching values
    cout << "Aggregating the matching for key " << *key << endl;
    
    Aggregates::iterator agt;
    Aggregates* agts = query->aggregates;
    for(agt = agts->begin(); agt != agts->end(); agt++) {
      row[(*agt)->alias()] = Value((*agt)->calculate(matching));
    }
    
    resultset.rows.push_back(row);
  }
  
	return true;
}
