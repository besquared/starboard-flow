/*
 *  IN.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "IN.h"

IN::IN(const string& column, const vector<string>& values) :
Condition::Condition(column) {
	this->values = values;
	this->negation = false;
	this->type = Condition::IN;
}

IN::IN(const string& column, const vector<string>& values, bool negation) :
Condition::Condition(column) {
	this->values = values;
	this->negation = negation;
	this->type = Condition::IN;
}

void IN::Apply(vector<string>& values) {
	values = Common::Intersect(values, this->values);
}

void IN::ApplyNegation(vector<string>& values) {
	// THIS DOESN'T WORK YET
	values = Common::Difference(values, this->values);
}
