/*
 *  Sequential.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sequential.h"

Executive::Sequential::Sequential(Domain::Base* domain, Query::Sequential* query) :
Executive::Base::Base(domain) {
	this->constructor = new Pipeline::Constructor();
	this->gatherer = new Pipeline::Gatherer();
  this->scanner = new Pipeline::Scanner();
	this->aggregator = new Pipeline::Aggregator();
}

Executive::Sequential::~Sequential() {
	delete(this->constructor);
	delete(this->gatherer);
  delete(this->scanner);
	delete(this->aggregator);
}

bool Executive::Sequential::Execute(ResultSet& results) {
  vector<WorkSet> workset;
	this->constructor->Execute(domain, query, workset);
	this->gatherer->Execute(domain, query, workset);
  
  Engine::MatchSet matchset;
  this->scanner->Execute(domain, query, workset, matchset);  
	this->aggregator->Execute(domain, query, workset, matchset, results);
  
	return true;
}