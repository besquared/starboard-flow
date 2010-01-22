/*
 *  Analytical.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_executive_analytical_h_
#define _flow_engine_executive_analytical_h_

#include "Base.h"
#include <Engine/Query/Analytical.h>
#include <Engine/Pipeline/Constructor.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Executive {
			class Analytical : public Executive::Base {				
			public:
				Analytical(Domain::Base* domain, Query::Base* query);
				
				bool Execute(Groups& results);
				
			protected:
				bool Aggregate(Groups& results);
				bool Sweep(Groups& base);
				bool Gather(const set<string>& measures, Groups& base);
			};
		}
	}
}

#endif