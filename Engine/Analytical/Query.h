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
#include <Engine/Aggregates.h>

#include "Groups.h"
#include "Executive.h"

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
				bool Execute(Groups& results);
				
				void Instantiate(map<string, string>& results);
				void Inquire(set<string>& dimensions, Conditions& conditions);
				void Dimensions(vector<string>& instantiated, vector<string>& inquired);
			};
		}
	}
}

#endif