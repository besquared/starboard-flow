/*
 *  MockExecutive.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_engine_executive_mock_analytical_h_
#define _flow_testing_engine_executive_mock_analytical_h_

#include "Common.h"
#include <Engine/Executive/Analytical.h>

using namespace Flow::Domain;
using namespace Flow::Engine;

namespace Flow {
	namespace Testing {
		namespace Engine {
			namespace Executive {
				class MockAnalytical : public ::Engine::Executive::Analytical {
				public:
					MockAnalytical(Domain::MockBase* domain, ::Query::Analytical* query) : 
					Flow::Engine::Executive::Analytical::Analytical(domain, query) {}
					
					MOCK_METHOD1(Execute, bool(Groups&));
				};
			}
		}
	}
}

#endif