/*
 *  Analytical.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Analytical.h"

Executive::Analytical::Analytical(Domain::Base* domain, Query::Base* query) :
Executive::Base::Base(domain, query) {
	this->constructor = new Pipeline::Constructor();
	this->gatherer = new Pipeline::Gatherer();
	this->aggregator = new Pipeline::Aggregator();
	this->sweeper = new Pipeline::Sweeper();
}

Executive::Analytical::~Analytical() {
	delete(this->constructor);
	delete(this->gatherer);
	delete(this->aggregator);
	delete(this->sweeper);
}

bool Executive::Analytical::Execute(Groups& results) {
	this->constructor->Execute(domain, query, results);
	this->gatherer->Execute(domain, query, results);
	this->aggregator->Execute(domain, query, results);
	this->sweeper->Execute(domain, query, results);
	return true;
}