/*
 *  Aggregate.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregation.h"

Aggregation::Aggregation(const string& measure) {
	this->measures.push_back(measure);
}

Aggregation::Aggregation(const vector<string>& measures) {
	this->measures = measures;
}