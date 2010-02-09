/*
 *  Scanner.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_pipeline_scanner_h_
#define _flow_engine_pipeline_scanner_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/MatchSet.h>
#include <Engine/Query/Sequential.h>
#include <Engine/Sequential/Match.h>
#include <Engine/Sequential/Scanner/Substring.h>

namespace Flow {
	namespace Engine {
		namespace Pipeline {
      using namespace std;
      using namespace Domain::Data;
            
			class Scanner {				
			public:
				bool Execute(Domain::Base* domain, Query::Sequential* query, 
                     vector<WorkSet>& worksets, MatchSet& matches);				
			};
		}
	}
}

#endif
