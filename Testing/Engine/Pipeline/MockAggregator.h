/*
 *  MockAggregator.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_engine_pipeline_mock_aggregator_h_
#define _flow_testing_engine_pipeline_mock_aggregator_h_

#include "Common.h"
#include <Engine/Pipeline/Aggregator.h>

namespace Flow {
	namespace Testing {
		namespace Engine {
			namespace Pipeline {        
        using namespace Flow::Domain;
        using namespace Flow::Engine;
        
				class MockAggregator : public ::Engine::Pipeline::Aggregator {
				public:
					MockAggregator() : Flow::Engine::Pipeline::Aggregator::Aggregator() {}
					
					MOCK_METHOD3(Execute, bool(::Domain::Base*, ::Query::Base*, vector<WorkSet>&));
          MOCK_METHOD4(Execute, bool(::Domain::Base*, ::Query::Base*, vector<WorkSet>&, MatchSet&));
				};
			}
		}
	}
}

#endif