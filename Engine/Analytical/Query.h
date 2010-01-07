/*
 *  Query.h
 *  Flow
 *
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_analytical_query_h_
#define _flow_engine_analytical_query_h_

#include <Common.h>
#include <Conditions.h>
#include <Domain/Base.h>
#include <Engine/Table.h>
#include <Engine/Aggregates.h>

#include "Groups.h"

using namespace std;
using namespace Flow;
using namespace Flow::Domain;
using namespace Flow::Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Query {
			public:
				Domain::Base* domain;
				Conditions* conditions;
				Aggregates* aggregates;
				
				Query(Domain::Base* domain);
				
				/*
				 * Querying
				 */
				bool Execute(Groups& results);
				bool Materialize(Groups& results);
				bool Aggregate(Groups& results);
				bool Gather(const set<string>& measures, Groups& base);
				bool Sweep(Groups& base);
				
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