/*
 *  Analytical.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Analytical.h"

Executive::Analytical::Analytical(Domain::Base* domain, Query::Analytical* query) :
Executive::Base::Base(domain) {
	this->constructor = new Pipeline::Constructor();
	this->gatherer = new Pipeline::Gatherer();
	this->aggregator = new Pipeline::Aggregator();
}

Executive::Analytical::~Analytical() {
	delete(this->constructor);
	delete(this->gatherer);
	delete(this->aggregator);
}

bool Executive::Analytical::Execute(ResultSet& resultset) {
  vector<WorkSet> intermediate;
  
	this->constructor->Execute(domain, query, intermediate);
	this->gatherer->Execute(domain, query, intermediate);
	this->aggregator->Execute(domain, query, intermediate);
	return true;
}