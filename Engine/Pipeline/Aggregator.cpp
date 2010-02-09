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
                                   vector<WorkSet>& worksets, MatchSet& matchset, ResultSet& results) {
  
  vector<string> grouping_dims = query->sequence_group_by;
  set<string> pattern_dims = query->pattern.dimensions();
  set<string> aggregate_dims = query->aggregates->aliases();
  
  results.columns.insert(results.columns.end(), grouping_dims.begin(), grouping_dims.end());
  results.columns.insert(results.columns.end(), pattern_dims.begin(), pattern_dims.end());
  results.columns.insert(results.columns.end(), aggregate_dims.begin(), aggregate_dims.end());
	
  // WE HAVE ZE MATCHSET
  vector<size_t>::iterator key;
  for(key = matchset.keys.begin(); key != matchset.keys.end(); key++) {
    Matching& matching = matchset[*key];
    
    // make row here with matching values
    
    Aggregates::iterator aggregate;
    Aggregates* aggregates = query->aggregates;
    for(aggregate = aggregates->begin(); aggregate != aggregates->end(); aggregate++) {
      double value = (*aggregate)->calculate(matching);
    }
  }
  
	return true;
}
