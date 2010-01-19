/*
 *  Executive.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_analytical_executive_h_
#define _flow_engine_analytical_executive_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Executive/Base.h>
#include <Engine/Executive/Constructor.h>

#include "Query.h"

using namespace std;
using namespace Flow;
using namespace Flow::Domain;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Query; // Forward Declaration
			
			class Executive : Executive::Base {
			protected:
				Domain::Base* domain;
				Analytical::Query* query;

			public:
				Executive(Domain::Base* domain, Analytical::Query* query);
				virtual bool Execute(Groups& results);
				
			protected:
				bool Aggregate(Groups& results);
				bool Sweep(Groups& base);
				bool Gather(const set<string>& measures, Groups& base);
			};
		}
	}
}

#endif