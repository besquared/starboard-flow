/*
 *  Scanner.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Scanner.h"

bool Pipeline::Scanner::Execute(Domain::Base* domain, Query::Base* query, Groups& results) {
  // what does the scanner do?
  
  // creates new groups/group structure with the proper group by/sequence by
  //  values and then scans the groups we have already, we then iterate over
  //  the matches and copy chunks of sequences from the old results into the
  //  new results
  
  return true;
}