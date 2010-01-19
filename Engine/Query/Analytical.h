/*
 *  Analytical.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_query_analytical_h_
#define _flow_engine_query_analytical_h_

#include "Base.h"

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Query {
			class Analytical : Query::Base {
			public:
				Analytical();				
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