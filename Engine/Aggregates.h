/*
 *  Aggregates.h
 *  flow
 *
 *  Created by Josh Ferguson on 12/21/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_aggregates_h_
#define _flow_aggregates_h_

#include "Common.h"

using namespace std;
using namespace Flow;

namespace Flow {
	class Aggregates : public vector<Aggregate> {
	public:
		void Count(const string& name);
		void Sum(const string& name);
	};
}

#endif