/*
 *  Base.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_query_base_h_
#define _flow_engine_query_base_h_

#include <Common.h>
#include <Conditions.h>
#include <Engine/Groups.h>
#include <Engine/Aggregates.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Query {
			class Base {
			public:
				Conditions* conditions;
				Aggregates* aggregates;

				Base() {
					this->conditions = new Conditions();
					this->aggregates = new Aggregates();
				}
				
				virtual ~Base() {
					delete(this->conditions);
					delete(this->aggregates);
				}
				
				// Set of measures we need to gather
				virtual void Measures(set<string>& results) = 0;
				
				// Set of dimensions we need to gather
				virtual void Dimensions(set<string>& results) = 0;
				
				// Information about fixed dimensions
				virtual void Instantiate(map<string, string>& results) = 0;
				virtual void InstantiatedValues(vector<string>& results) = 0;
				
				// Information about predicated dimensions
				virtual void Inquire(set<string>& dimensions, Conditions& conditions) = 0;
				
				// Convenience lists of dimensions we're instantiating and inquiring
				virtual void Dimensions(vector<string>& instantiated, vector<string>& inquired) = 0;
			};
		}
	}
}

#endif