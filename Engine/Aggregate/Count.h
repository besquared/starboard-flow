/*
 *  Count.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_aggregate_count_h_
#define _flow_aggregate_count_h_

#include <Common.h>

#include "Base.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		namespace Aggregate {
			class Count : public Aggregate::Base {		
			public:
				Count(const string& measure);
				Count(const string& measure, const string& alias);
				
				virtual string alias();
        virtual void apply(WorkSet& workset);
				virtual void apply(vector<WorkSet>& worksets);
        virtual double calculate(Matching& matching);
			};
		}
	}
}

#endif