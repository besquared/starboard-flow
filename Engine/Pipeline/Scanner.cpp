/*
 *  Scanner.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Scanner.h"

bool Pipeline::Scanner::Execute(Domain::Base* domain, Query::Sequential* query, Groups& groups, Sequential::Matches& matches) {
  Sequential::Scanner::Substring scanner;
  scanner.execute(query->pattern, groups, matches);
  return true;
}