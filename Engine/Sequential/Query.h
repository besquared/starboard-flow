/*
 *  Query.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_query_h_
#define _flow_engine_sequential_query_h_

#include <Common.h> 
#include <Conditions.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Aggregates.h>

#include "Pattern.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;
using namespace Flow::Domain;
using namespace Flow::Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Sequential {
			class Query {
			public:
				Conditions* conditions;
				Aggregates* aggregates;
				
				Query();
				~Query();
				bool Execute(Domain::Base* domain, Groups& results);
				bool Execute(Executive& executive, Groups& results);
								
				bool Aggregate(Table& results);
				bool Sweep(Table& base);

				bool GatherMeasures(const set<string>& measures, Table& base);
				bool GatherDimensions(const set<string>& dimensions, Table& base);
			};
		}
	}
}

#endif