/*
 *  Scanner.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Scanner.h"

bool Pipeline::Scanner::Execute(Domain::Base* domain, Query::Sequential* query, 
                                vector<WorkSet>& worksets, MatchSet& matchset) {
  
  Sequential::Matches matches;
  Sequential::Scanner::Substring scanner;
  scanner.execute(query->pattern, worksets, matches);
  
  // assemble matchset here
  
  vector<string> groupby = query->sequence_group_by;
  
  map<string, string> keymap;
  map<string, string> groupbymap;
  Sequential::Matches::iterator matchlist;
  vector<Sequential::Match>::iterator match;
  for(matchlist = matches.begin(); matchlist != matches.end(); matchlist++) {
    WorkSet& matched = worksets[matchlist->first];

    vector<string>::iterator dim;
    for(dim = groupby.begin(); dim != groupby.end(); dim++) {
      groupbymap[*dim] = matched.values[*dim];
    }
    
    for(match = matchlist->second.begin(); match != matchlist->second.end(); match++) {
      keymap.insert(groupbymap.begin(), groupbymap.end());
      keymap.insert(match->tvalues.begin(), match->tvalues.end());
      matchset.insert(keymap, *match);
      keymap.clear();
    }
  }
  
  return true;
}