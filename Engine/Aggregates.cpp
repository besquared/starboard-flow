/*
 *  Aggregates.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregates.h"

void Engine::Aggregates::Count(const string& name) {
	shared_ptr<Aggregate::Count> count(new Aggregate::Count(name));
	vector< shared_ptr<Aggregate::Base> >::push_back(count);
}

void Engine::Aggregates::Sum(const string& name) {
	shared_ptr<Aggregate::Sum> sum(new Aggregate::Sum(name));
	vector< shared_ptr<Aggregate::Base> >::push_back(sum);
}