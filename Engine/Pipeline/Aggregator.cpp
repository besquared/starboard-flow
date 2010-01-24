/*
 *  Aggregator.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregator.h"

bool Pipeline::Aggregator::Execute(Domain::Base* domain, Query::Base* query, Groups& results) {
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(results);
	}
	
	return true;
}
