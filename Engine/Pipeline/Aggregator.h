/*
 *  Aggregator.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/22/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_pipeline_aggregator_h_
#define _flow_engine_pipeline_aggregator_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/ResultSet.h>
#include <Engine/Query/Analytical.h>
#include <Engine/Query/Sequential.h>
#include <Engine/Sequential/Match.h>

using namespace std;
using namespace Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Pipeline {		
			class Aggregator {				
			public:
				bool Execute(Domain::Base* domain, Query::Analytical* query, Groups& groups);
				bool Execute(Domain::Base* domain, Query::Sequential* query, Groups& groups, Sequential::Matches& matches, ResultSet& results);
			};
		}
	}
}

#endif
