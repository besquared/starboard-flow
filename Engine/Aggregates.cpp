/*
 *  Aggregates.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregates.h"
#include "Aggregates/Count.h"
#include "Aggregates/Sum.h"

void Aggregates::Count(const string& name) {
	vector<Aggregate>::push_back(Count(name));
}

void Aggregates::Sum(const string& name) {
	vector<Aggregate>::push_back(Sum(name));
}