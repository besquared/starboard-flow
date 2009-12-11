/*
 *  LT.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "LT.h"

LT::LT(const string& column, const string& value) :
Condition::Condition(column) {
	this->value = value;
	this->type = Condition::LT;
}

void LT::Apply(vector<string>& values) {
	vector<string> results;
	results.reserve(values.size());
	size_t vsize = values.size();
	for(size_t i = 0; i < vsize; i++) {
		if(values[i] < this->value) {
			results.push_back(values[i]);
		}
	}
	values = results;
}