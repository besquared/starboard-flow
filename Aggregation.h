/*
 *  Aggregate.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _aggregation_included_
#define _aggregation_included_

#include "Common.h"
#include "Table.h"

namespace Flow {
  class Aggregation {		
	public:
		vector<string> measures;
		
		Aggregation(const string& measure);
		Aggregation(const vector<string>& measure);
		virtual void Apply(shared_ptr<Table> base) = 0;		
	};
}

#endif