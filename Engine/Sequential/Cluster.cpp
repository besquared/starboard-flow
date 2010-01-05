/*
 *  Cluster.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/5/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Cluster.h"

using namespace Flow::Engine;

Sequential::Cluster::Cluster(const vector<string>& dimensions) {
	this->dimensions = dimensions;
}

void Sequential::Cluster::Insert(double record, vector<string>& values) {
	this->Insert(record, values.begin(), values.end());
}
