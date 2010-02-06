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

bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Base* query, Groups& results) {
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(results);
	}
	
	return true;
}

// Iterate over matches, aggregate them, put those into new groups
bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Base* query, Groups& groups, Sequential::Matches& matches, ResultSet& results) {
  
  // go through matches and make new groups by copying sequences
  // how do we know what the final groups will be? which dimensions?
  // sequence group by fare-group, day
//  Engine::Groups groups(query->sequence_group_by);
  
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
