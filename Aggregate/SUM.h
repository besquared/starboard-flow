/*
 *  SUM.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _sum_included_
#define _sum_included_

#include "Common.h"

#include "Table.h"
#include "Aggregation.h"

namespace Flow {
  class SUM : public Aggregation {		
	public:
		SUM(const string& measure);
		void Apply(shared_ptr<Table> base);		
	};
}

#endif