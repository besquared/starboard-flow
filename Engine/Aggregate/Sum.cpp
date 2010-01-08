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

string Aggregate::Sum::alias() {
	return "sum_" + measure;
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
	vector<double> values = group.measures(measure);
	for(value = values.begin(); value != values.end(); value++) {
		sum += *value;
	}
	group.aggregate(alias(), sum);
}