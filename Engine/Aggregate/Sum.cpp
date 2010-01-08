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

void Aggregate::Sum::Apply(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		this->Apply(*group);
	}
}

void Aggregate::Sum::Apply(Group& group) {
	vector<double> values = group.measures[measure];
	
	double sum = 0;
	vector<double>::iterator value;
	for(value = values.begin(); value != values.end(); value++) {
		sum += *value;
	}
	
	group.aggregates[alias] = sum;
}