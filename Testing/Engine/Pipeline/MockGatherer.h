/*
 *  MockGatherer.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_engine_pipeline_mock_gatherer_h_
#define _flow_testing_engine_pipeline_mock_gatherer_h_

#include "Common.h"
#include <Engine/Pipeline/Gatherer.h>

namespace Flow {
	namespace Testing {
		namespace Engine {
			namespace Pipeline {
        using namespace Flow::Domain;
        using namespace Flow::Engine;
                
				class MockGatherer : public ::Engine::Pipeline::Gatherer {
				public:
					MockGatherer() : Flow::Engine::Pipeline::Gatherer::Gatherer() {}
					
					MOCK_METHOD3(Execute, bool(::Domain::Base*, ::Query::Base*, vector<WorkSet>&));
				};
			}
		}
	}
}

#endif