/*
 *  Sum.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_aggregates_sum_h_
#define _flow_aggregates_sum_h_

#include <Common.h>
#include "Engine/Aggregate/Base.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		namespace Aggregate {
			class Sum : public Aggregate::Base {		
			public:
				Sum(const string& measure);
				void Apply(Table& base);		
			};
		}
	}
}

#endif