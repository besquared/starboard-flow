/*
 *  EQ.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/9/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "EQ.h"

EQ::EQ(const string& column, const string& value) :
Condition::Condition(column) {
	this->value = value;
	this->negation = false;
	this->type = Condition::EQ;
}

EQ::EQ(const string& column, const string& value, bool negation) :
Condition::Condition(column) {
	this->value = value;
	this->negation = negation;
	this->type = Condition::EQ;
}

void EQ::Apply(vector<string>& values) {
	if(this->negation) {
		this->ApplyNegation(values);
	} else {
		vector<string> results;
		results.reserve(values.size());
		size_t vsize = values.size();
		for(size_t i = 0; i < vsize; i++) {
			if(values[i] == this->value) {
				results.push_back(values[i]);
			}
		}
		values = results;
	}
}

void EQ::ApplyNegation(vector<string>& values) {
	vector<string> results;
	results.reserve(values.size());
	size_t vsize = values.size();
	for(size_t i = 0; i < vsize; i++) {
		if(values[i] != this->value) {
			results.push_back(values[i]);
		}
	}
	values = results;
}
