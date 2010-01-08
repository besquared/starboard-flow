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
	group.aggregates[alias] = group.measures[measure].size();
	
//	size_t column_size = column->size();
//	for(size_t i = 0; i < column_size; i++) {
//		vector<double> members = column->at(i);
//		
//		double sum = 0;
//		size_t member_size = members.size();
//		for(size_t j = 0; j < member_size; j++) {
//			sum += members[j];
//		}
//		aggregated->push_back(sum);
//	}	
//	base.push_back(aggregated);	
}