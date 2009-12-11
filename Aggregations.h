/*
 *  Aggregations.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _aggregations_included_
#define _aggregations_included_

#include "Common.h"
#include "Aggregation.h"

#include "COUNT.h"
#include "SUM.h"

namespace Flow {
  class Aggregations : public vector< shared_ptr<Aggregation> > {
  public:
		void count(const string& column);
		void sum(const string& column);
  };
}

#endif