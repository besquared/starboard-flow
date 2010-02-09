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
                                   vector<WorkSet>& worksets, Sequential::Matches& matches, ResultSet& results) {
  
  vector<string> grouping_dims = query->sequence_group_by;
  set<string> pattern_dims = query->pattern.dimensions();
  set<string> aggregate_dims = query->aggregates->aliases();
  
  results.columns.insert(results.columns.end(), grouping_dims.begin(), grouping_dims.end());
  results.columns.insert(results.columns.end(), pattern_dims.begin(), pattern_dims.end());
  results.columns.insert(results.columns.end(), aggregate_dims.begin(), aggregate_dims.end());
  
  //
  // oh wow this just got hard, one result set row could span multiple matches
  //
  Sequential::Matches::iterator match;
  vector<Sequential::Match>::iterator indices;
  for(match = matches.begin(); match != matches.end(); match++) {
    map<string, Value> row;
    WorkSet& matched = worksets[match->first];
    
    // insert grouping dimensions into row
    // this is wrong, this needs to be in key form
    vector<string>::iterator dimension;
    for(dimension = grouping_dims.begin(); dimension != grouping_dims.end(); dimension++) {
//      row[*dimension] = Engine::Value(matched.values[*dimension]);
    }
    
    for(indices = match->second.begin(); indices != match->second.end(); indices++) {
      cout << "Aggregating and assinging sequence from position " << indices->position << " of group " << match->first << endl;
    }
  }
	
	return true;
}
