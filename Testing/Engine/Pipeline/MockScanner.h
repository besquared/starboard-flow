/*
 *  MockScanner.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/10/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_engine_pipeline_mock_scanner_h_
#define _flow_testing_engine_pipeline_mock_scanner_h_

#include "Common.h"
#include <Engine/Pipeline/Scanner.h>

namespace Flow {
	namespace Testing {
		namespace Engine {
			namespace Pipeline {
        using namespace Flow::Domain;
        using namespace Flow::Engine;
        
				class MockScanner : public ::Engine::Pipeline::Scanner {
				public:
					MockScanner() : Flow::Engine::Pipeline::Scanner::Scanner() {}
					
					MOCK_METHOD4(Execute, bool(::Domain::Base*, ::Query::Base*, vector<WorkSet>&, MatchSet&));
				};
			}
		}
	}
}

#endif