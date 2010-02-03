/*
 *  Scanner.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Scanner.h"

bool Pipeline::Scanner::Execute(Domain::Base* domain, Query::Sequential* query, Groups& results) {
  // scan like a boss
  
  Sequential::Scanner::Matches matches;
  Sequential::Scanner::Substring scanner;
  scanner.execute(query->pattern, results, matches);
  
  // go through matches and make new groups by copying sequences
  // how do we know what the final groups will be? which dimensions?
  // sequence group by fare-group, day
  Engine::Groups groups(query->sequence_group_by);
  
  Sequential::Scanner::Matches::iterator match;
  vector<Sequential::Scanner::Match>::iterator indices;
  for(match = matches.begin(); match != matches.end(); match++) {
    Group& matched = results[match->first];
    for(indices = match->second.begin(); indices != match->second.end(); indices++) {
      cout << "Copying sequence from position " << indices->position << " of group " << match->first << endl;
    }
    
    groups.push_back(matched);
  }
  
  
  return true;
}