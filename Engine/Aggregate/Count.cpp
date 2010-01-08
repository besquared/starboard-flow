/*
 *  Count.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Count.h"

Aggregate::Count::Count(const string& measure) : 
Aggregate::Base::Base(measure) {}

string Aggregate::Count::alias() {
	return "count_" + measure;
}

void Aggregate::Count::apply(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		this->apply(*group);
	}
}

void Aggregate::Count::apply(Group& group) {	
	group.aggregate(alias(), group.measures(measure).size());
}