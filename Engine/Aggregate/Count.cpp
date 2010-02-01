/*
 *  Count.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Count.h"

Aggregate::Count::Count() :
Aggregate::Base::Base() {}

Aggregate::Count::Count(const string& measure) : 
Aggregate::Base::Base(measure) {}

Aggregate::Count::Count(const string& measure, const string& alias) :
Aggregate::Base::Base(measure, alias) {}

string Aggregate::Count::alias() {
	if(alias_.empty()) {
		return "count_" + measure;
	} else {
		return alias_;
	}
}

void Aggregate::Count::apply(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		this->apply(*group);
	}
}

void Aggregate::Count::apply(Group& group) {	
	group.aggregates[alias()] = group.records.size();
}