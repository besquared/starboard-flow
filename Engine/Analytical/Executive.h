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

#include "Query.h"
#include "Groups.h"

using namespace std;
using namespace Flow;
using namespace Flow::Domain;
using namespace Flow::Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Query; // Forward Declaration
			
			class Executive {
			protected:
				Query* query;

			public:
				Executive(Query* query);
				virtual bool Execute(Groups& results);
				
			protected:
				bool Materialize(Groups& results);
				bool Aggregate(Groups& results);
				bool Sweep(Groups& base);
				bool Gather(const set<string>& measures, Groups& base);

			protected:
				/*
				 * Constructing Results
				 */
				void Construct(RIDList& instantiated, RIDTree& inquired, 
											 vector<string>& dimensions, Groups& results);
				void Construct(RIDList& instantiated, RIDTree& inquired, 
											 vector<string>& dimensions, int offset, 
											 vector<string>& values, RIDList& records, 
											 Groups& results);				
			};
		}
	}
}

#endif