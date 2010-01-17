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
#include <Engine/Groups.h>
#include <Engine/Aggregates.h>

#include "Executive.h"

using namespace std;
using namespace Flow;
using namespace Flow::Domain;
using namespace Flow::Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Executive;
			
			class Query {
			public:
				Conditions* conditions;
				Aggregates* aggregates;
				
				Query();
				~Query();
				bool Execute(Domain::Base* domain, Groups& results);
				bool Execute(Executive& executive, Groups& results);
				
				void Measures(set<string>& results);
				void Instantiate(map<string, string>& results);
				void InstantiatedValues(vector<string>& results);
				void Inquire(set<string>& dimensions, Conditions& conditions);
				void Dimensions(vector<string>& instantiated, vector<string>& inquired);
			};
		}
	}
}

#endif