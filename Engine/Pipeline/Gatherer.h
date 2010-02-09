/*
 *  Gatherer.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_pipeline_gatherer_h_
#define _flow_engine_pipeline_gatherer_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Query/Base.h>

using namespace std;
using namespace Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Pipeline {		
			class Gatherer {				
			public:
        bool Execute(Domain::Base* domain, Query::Base* query, WorkSet& workset);
				bool Execute(Domain::Base* domain, Query::Base* query, vector<WorkSet>& worksets);				
			};
		}
	}
}

#endif
