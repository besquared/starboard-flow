/*
 *  Sweeper.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sweeper.h"

bool Pipeline::Sweeper::Execute(Domain::Base* domain, Query::Base* query, Groups& results) {
	Groups::iterator group;
	for(group = results.begin(); group != results.end(); group++) {
		group->clear();
		group->clear_measures();
	}
	
	return true;
}
