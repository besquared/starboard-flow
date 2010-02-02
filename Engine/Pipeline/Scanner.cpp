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
  Sequential::Scanner::Matches::iterator match;
  for(match = matches.begin(); match != matches.end(); match++) {
    
  }
  
  
  return true;
}