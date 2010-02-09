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

  vector<string> groupdims = query->sequence_group_by;
  
  size_t matchkey = 0;
  map<string, string> keymap;
  Sequential::Matches::iterator matchlist;
  vector<Sequential::Match>::iterator match;
  for(matchlist = matches.begin(); matchlist != matches.end(); matchlist++) {
    WorkSet& matched = worksets[matchlist->first];
    
    vector<string>::iterator dim;
    for(match = matchlist->second.begin(); match != matchlist->second.end(); match++) {
      for(dim = groupdims.begin(); dim != groupdims.end(); dim++) {
        keymap[*dim] = matched.values[*dim];
      }
      
      keymap.insert(match->tvalues.begin(), match->tvalues.end());
      
      map<string, string>::iterator keypart;
      for(keypart = keymap.begin(); keypart != keymap.end(); keypart++) {
        boost::hash_combine(matchkey, keypart->first);
        boost::hash_combine(matchkey, keypart->second);
      }
      
      matchset.insert(matchkey, *match);
      
      matchkey = 0;
      keymap.clear();
    }
  }
  
  return true;
}