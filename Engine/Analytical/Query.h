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
#include <Engine/Aggregates.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Query {
			public:
				
				Query();
				~Query();
				
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