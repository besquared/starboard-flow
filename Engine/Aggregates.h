/*
 *  Aggregates.h
 *  flow
 *
 *  Created by Josh Ferguson on 12/21/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_aggregates_h_
#define _flow_engine_aggregates_h_

#include "Common.h"
#include "Engine/Aggregate/Count.h"
#include "Engine/Aggregate/Sum.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		class Aggregates : public vector< shared_ptr<Aggregate::Base> > {
		public:
			void Count(const string& name);
			void Sum(const string& name);
		};
	}
}

#endif