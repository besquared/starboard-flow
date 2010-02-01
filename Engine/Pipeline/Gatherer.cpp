/*
 *  Gatherer.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Gatherer.h"

// Make this multithreaded
bool Pipeline::Gatherer::Execute(Domain::Base* domain, Query::Base* query, Groups& results) {
	set<string> measures;
	set<string> dimensions;
	Groups::iterator group;

	query->Measures(measures);
	query->Dimensions(dimensions);

	set<string>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		for(group = results.begin(); group != results.end(); group++) {
			if(*measure != "records") {
				domain->measures->Lookup(*measure, group->records, group->measures[*measure]);
			}
		}
	}
	
	set<string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		for(group = results.begin(); group != results.end(); group++) {
			domain->dimensions->Lookup(*dimension, group->records, group->dimensions[*dimension]);
		}
	}	
	
	return true;
}