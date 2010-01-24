/*
 *  MockSweeper.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_engine_pipeline_mock_sweeper_h_
#define _flow_testing_engine_pipeline_mock_sweeper_h_

#include "Common.h"
#include <Engine/Pipeline/Sweeper.h>

using namespace Flow::Domain;
using namespace Flow::Engine;

namespace Flow {
	namespace Testing {
		namespace Engine {
			namespace Pipeline {
				class MockSweeper : public ::Engine::Pipeline::Sweeper {
				public:
					MockSweeper() : Flow::Engine::Pipeline::Sweeper::Sweeper() {}
					
					MOCK_METHOD3(Execute, bool(::Domain::Base*, ::Query::Base*, Groups&));
				};
			}
		}
	}
}

#endif