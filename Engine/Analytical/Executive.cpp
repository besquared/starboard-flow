/*
 *  Executive.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Executive.h"

using namespace Flow::Engine;

Analytical::Executive::Executive(Domain::Base* domain, Query* query) {
	this->domain = domain;
	this->query = query;
}

bool Analytical::Executive::Execute(Groups& results) {
	Executive::Constructor constructor().Execute(domain, query, results);
	if(!this->Aggregate(results)) return false;
	if(!this->Sweep(results)) return false;
	return true;
}

bool Analytical::Executive::Aggregate(Groups& base) {	
	set<string> measures;
	query->Measures(measures);
	this->Gather(measures, base);
	for(size_t j = 0; j < query->aggregates->size(); j++) {
		query->aggregates->apply(base);
	}
	
	return true;
}

// Gather all the measures needed by the aggregates
bool Analytical::Executive::Gather(const set<string>& measures, Groups& base) {
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

bool Analytical::Executive::Sweep(Groups& base) {
	Groups::iterator group;
	for(group = base.begin(); group != base.end(); group++) {
		group->clear();
		group->clear_measures();
	}
	
	return true;
}