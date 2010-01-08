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

void Aggregate::Count::Apply(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		this->Apply(*group);
	}
}

void Aggregate::Count::Apply(Group& group) {	
	group.aggregates[alias] = group.measures[measure].size();
}