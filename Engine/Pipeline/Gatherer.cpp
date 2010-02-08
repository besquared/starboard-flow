/*
 *  Gatherer.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Gatherer.h"

bool Pipeline::Gatherer::Execute(Domain::Base* domain, Query::Base* query, WorkSet& workset) {
  set<string> measures;
	set<string> dimensions;
	query->Measures(measures);
	query->Dimensions(dimensions);
  
	set<string>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
    if(*measure != "records") {
      domain->measures->Lookup(*measure, workset.records, workset.measures[*measure]);
    }
	}
	
	set<string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		domain->dimensions->Lookup(*dimension, workset.records, workset.dimensions[*dimension]);
	}
  
  return true;
}


bool Pipeline::Gatherer::Execute(Domain::Base* domain, Query::Base* query, vector<WorkSet>& worksets) {
  vector<WorkSet>::iterator workset;
  for(workset = worksets.begin(); workset != worksets.end(); workset++) {
    Execute(domain, query, *workset);
  }
	
	return true;
}