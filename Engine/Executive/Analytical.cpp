/*
 *  Analytical.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Analytical.h"

bool Executive::Analytical::Execute(Groups& results) {
	Executive::Constructor().Execute(domain, query, results);
	if(!this->Aggregate(results)) return false;
	if(!this->Sweep(results)) return false;
	return true;
}

bool Executive::Analytical::Aggregate(Groups& base) {	
	set<string> measures;
	query->Measures(measures);
	this->Gather(measures, base);
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(base);
	}
	
	return true;
}

// Gather all the measures needed by the aggregates
bool Executive::Analytical::Gather(const set<string>& measures, Groups& base) {
	// Make this multithreaded
	Groups::iterator group;
	set<string>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		for(group = base.begin(); group != base.end(); group++) {
			if(*measure != "records") {
				domain->measures->Lookup(*measure, *group, group->measures(*measure));
			}
		}
	}
	
	return true;
}

bool Executive::Analytical::Sweep(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		group->clear();
		group->clear_measures();
	}
	
	return true;
}