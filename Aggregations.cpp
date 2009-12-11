/*
 *  Aggregations.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregations.h"

void Aggregations::count(const string& name) {
	vector< shared_ptr<Aggregation> >::push_back(shared_ptr<Aggregation>(new COUNT(name)));
}

void Aggregations::sum(const string& name) {
	vector< shared_ptr<Aggregation> >::push_back(shared_ptr<Aggregation>(new SUM(name)));
}