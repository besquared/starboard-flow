/*
 *  COUNT.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#ifndef _count_included_
#define _count_included_

#include "Common.h"
#include "Table.h"
#include "Aggregation.h"

namespace Flow {
  class COUNT : public Aggregation {		
	public:
		COUNT(const string& measure);
		void Apply(shared_ptr<Table> base);		
	};
}

#endif