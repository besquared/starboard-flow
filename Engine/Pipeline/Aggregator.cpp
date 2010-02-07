/*
 *  Aggregator.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Engine/Sequential/Match.h>

#include "Aggregator.h"

bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Analytical* query, Groups& results) {
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(results);
	}
	
	return true;
}

// Iterate over matches, aggregate them, put those into new groups
bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Sequential* query, Groups& groups, Sequential::Matches& matches, ResultSet& results) {
  vector<string> grouping_dimensions = query->sequence_group_by;
  set<string> pattern_dimensions = query->pattern.dimensions();
  set<string> aggregate_dimensions = query->aggregates->aliases();
  
  results.columns.insert(results.columns.end(), 
                         grouping_dimensions.begin(), 
                         grouping_dimensions.end());
  results.columns.insert(results.columns.end(),
                         pattern_dimensions.begin(),
                         pattern_dimensions.end());
  results.columns.insert(results.columns.end(),
                         aggregate_dimensions.begin(),
                         aggregate_dimensions.end());
  
  //  and aggregate dimensions COUNT(*), AVG_INTERVAL(X, Y), etc.
  
  Sequential::Matches::iterator match;
  vector<Sequential::Match>::iterator indices;
  for(match = matches.begin(); match != matches.end(); match++) {
    Group& matched = groups[match->first];
    for(indices = match->second.begin(); indices != match->second.end(); indices++) {
      cout << "Aggregating and assinging sequence from position " << indices->position << " of group " << match->first << endl;
    }
//    groups.push_back(matched);
  }
  
  //	for(size_t j = 0; j < query->aggregates->size(); j++) {
//		query->aggregates->apply(results);
//	}
	
	return true;
}
