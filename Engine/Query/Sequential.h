/*
 *  Sequential.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_query_sequential_h_
#define _flow_engine_query_sequential_h_

#include <Engine/Sequential/Pattern.h>

#include "Base.h"

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Query {
			class Sequential : public Query::Base {
			public:
        vector<string> cluster_by;
        vector<string> sequence_group_by;
        Engine::Sequential::Pattern pattern;
        
				Sequential();
				void Measures(set<string>& results);
				void Dimensions(set<string>& results);
				
				void Instantiate(map<string, string>& results);
				void InstantiatedValues(vector<string>& results);
				
				void Inquire(set<string>& dimensions, Conditions& conditions);
				
				void Dimensions(vector<string>& instantiated, vector<string>& inquired);
			};
		}
	}
}

#endif