/*
 *  MockExecutive.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_engine_analytical_mock_executive_h_
#define _flow_testing_engine_analytical_mock_executive_h_

#include "Common.h"
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Analytical/Query.h>
#include <Engine/Analytical/Executive.h>

using namespace Flow::Domain;
using namespace Flow::Engine::Analytical;

namespace Flow {
	namespace Testing {
		namespace Engine {
			namespace Analytical {
				class MockExecutive : public ::Engine::Analytical::Executive {
				public:
					MockExecutive(Domain::MockBase* domain, Query* query) : 
					Flow::Engine::Analytical::Executive::Executive(domain, query) {}
					
					MOCK_METHOD1(Execute, bool(Groups&));
				};
			}
		}
	}
}

#endif