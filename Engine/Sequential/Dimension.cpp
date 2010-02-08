/*
 *  Dimension.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimension.h"

Engine::Sequential::Dimension::Dimension(const string& name, const string& symbol, const string& alias) {
	this->name = name;
	this->symbol = symbol;
	this->alias = alias;
}

Engine::Sequential::Dimension::Dimension(const string& name, const string& symbol, const string& alias, const Conditions& conditions) {
	this->name = name;
	this->symbol = symbol;
	this->alias = alias;
	this->conditions = conditions;
}

bool Engine::Sequential::Dimension::match(WorkSet& workset, Match& match, size_t position) {  
  map<string, string>::iterator found = match.tvalues.find(symbol);
  
  if(found == match.tvalues.end()) {
    match.tvalues[symbol] = workset.dimensions[name][position];
  } else if(workset.dimensions[name][position] != found->second) {
    return false;
  }
  
  shared_ptr<Condition::Base> condition;
	for(size_t i = 0; i < conditions.size(); i++) {
		condition = conditions.at(i);
    
		if(condition != NULL) {
      // Condition check
			if(!condition->Check(workset.dimensions[condition->column][position])) {
        return false;
      }
		}
	}
  
  return true;
}