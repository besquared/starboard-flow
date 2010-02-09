/*
 *  Pattern.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Pattern.h"

using namespace Flow::Engine;

Sequential::Pattern::Pattern() {
	this->matching = SUBSTRING;
	this->restriction = LEFT_MATCH;
}

void Sequential::Pattern::push_back(const string& name, const string& symbol, const string& alias) {
	vector< boost::shared_ptr<Sequential::Dimension> >::push_back(
		boost::shared_ptr<Sequential::Dimension>(new Sequential::Dimension(name, symbol, alias))
	);
}

void Sequential::Pattern::push_back(const string& name, const string& symbol, const string& alias, const Conditions& conditions) {
	vector< boost::shared_ptr<Sequential::Dimension> >::push_back(
		boost::shared_ptr<Sequential::Dimension>(new Sequential::Dimension(name, symbol, alias, conditions))
	);
}

set<string> Sequential::Pattern::dimensions() {
  set<string> results;
  
  for(size_t i = 0; i < this->size(); i++) {
    results.insert(this->at(i)->symbol);
  }
  
  return results;
}

bool Sequential::Pattern::match(WorkSet& sequence, Match& result) {
  size_t offset = 1;
  while(offset <= size()) {
    if(this->at(offset - 1)->match(sequence, result, result.position + offset - 1)) {
      cout << "- Pattern matched at relative position " << offset - 1 << endl;
      offset++;
    } else {
      break;
    }
  }
  
  if(offset > size()) {
    return true;
  } else {
    return false;
  }
}
