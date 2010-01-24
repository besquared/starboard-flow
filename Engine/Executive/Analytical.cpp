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
Executive::Base::Base(domain, query) {}

bool Executive::Analytical::Execute(Groups& results) {
	Pipeline::Constructor().Execute(domain, query, results);
	Pipeline::Gatherer().Execute(domain, query, results);
	Pipeline::Aggregator().Execute(domain, query, results);
	Pipeline::Sweeper().Execute(domain, query, results);
	return true;
}