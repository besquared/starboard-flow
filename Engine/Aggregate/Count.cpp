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

Aggregate::Count::Count(const string& measure, const string& alias) :
Aggregate::Base::Base(measure, alias) {}

string Aggregate::Count::alias() {
	if(alias_.empty()) {
		return "count_" + measure;
	} else {
		return alias_;
	}
}

void Aggregate::Count::apply(WorkSet& workset) {	
	workset.aggregates[alias()] = workset.records.size();
}

void Aggregate::Count::apply(vector<WorkSet>& worksets) {
	vector<WorkSet>::iterator workset;
	for(workset = worksets.begin(); workset != worksets.end(); workset++) {
		this->apply(*workset);
	}
}

double Aggregate::Count::calculate(Matching& matching) {	
  return matching.matches.size();
  
	//workset.aggregates[alias()] = workset.keys.size();
}

