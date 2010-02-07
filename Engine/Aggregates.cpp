/*
 *  Aggregates.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregates.h"

void Engine::Aggregates::sum(const string& name) {
	shared_ptr<Aggregate::Sum> sum(new Aggregate::Sum(name));
	vector< shared_ptr<Aggregate::Base> >::push_back(sum);
}

void Engine::Aggregates::count(const string& name) {
	shared_ptr<Aggregate::Count> count(new Aggregate::Count(name));
	vector< shared_ptr<Aggregate::Base> >::push_back(count);
}

void Engine::Aggregates::apply(Groups& base_table) {
	for(size_t i = 0; i < size(); i++) {
		(*this)[i]->apply(base_table);
	}	
}

void Engine::Aggregates::measure_names(set<string>& results) {
	set<string> measures;
	for(size_t i = 0; i < size(); i++) {
		(*this)[i]->measure_names(measures);
		results.insert(measures.begin(), measures.end());
	}
}

// Set of output dimensions
set<string> Engine::Aggregates::aliases() {
  set<string> results;
  
  for(size_t i = 0; i < size(); i++) {
		results.insert(this->at(i)->alias());
	}
  
  return results;
}