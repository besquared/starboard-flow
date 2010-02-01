/*
 *  Sum.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sum.h"

Aggregate::Sum::Sum(const string& measure) : 
Aggregate::Base::Base(measure) {}

Aggregate::Sum::Sum(const string& measure, const string& alias) :
Aggregate::Base::Base(measure, alias) {}

string Aggregate::Sum::alias() {
	if(alias_.empty()) {
		return "sum_" + measure;
	} else {
		return alias_;
	}
}

void Aggregate::Sum::apply(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		this->apply(*group);
	}
}

void Aggregate::Sum::apply(Group& group) {
	double sum = 0;
	vector<double>::iterator value;
	vector<double> values = group.measures[measure];
	for(value = values.begin(); value != values.end(); value++) {
		sum += *value;
	}
	group.aggregates[alias()] = sum;
}