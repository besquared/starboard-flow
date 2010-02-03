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

bool Engine::Sequential::Dimension::match(Group& haystack, size_t position, Match& match) {  
  // Template check
  // ask whether or not the value of the sequence of the dimension 'name'
  //  matches the value in the match for our symbol.
  //  station, X
  //  {X => 'Montgomery'}
  //  haystack.dimensions[name][position] == match.tvalues[symbol]
  
  map<string, string>::iterator found = match.tvalues.find(symbol);
  
  if(found == match.tvalues.end()) {
    cout << "assiging tvalues[" << symbol << "] to haystack.dimensions[" << name << "][" << position << "]" << endl;
    match.tvalues[symbol] = haystack.dimensions[name][position];
  } else if(haystack.dimensions[name][position] != found->second) {
    return false;
  }
  
  shared_ptr<Condition::Base> condition;
	for(size_t i = 0; i < conditions.size(); i++) {
		condition = conditions.at(i);
    
		if(condition != NULL) {
      vector<string>& values = haystack.dimensions[condition->column];
      
      // OOB check
      if(position >= values.size()) {
        return false;
      }
      
      // Condition check
			if(!condition->Check(values[position])) {
        return false;
      }
		}
	}
  
  return true;
}