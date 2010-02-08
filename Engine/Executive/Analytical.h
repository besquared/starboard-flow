/*
 *  Analytical.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_executive_analytical_h_
#define _flow_engine_executive_analytical_h_

#include "Base.h"
#include <Engine/Query/Analytical.h>
#include <Engine/Pipeline/Constructor.h>
#include <Engine/Pipeline/Gatherer.h>
#include <Engine/Pipeline/Aggregator.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Executive {
			class Analytical : public Executive::Base {
			protected:
        Query::Analytical* query;

				Pipeline::Constructor* constructor;
				Pipeline::Gatherer* gatherer;
				Pipeline::Aggregator* aggregator;
				
			public:
				Analytical(Domain::Base* domain, Query::Analytical* query);
				virtual ~Analytical();
				
				virtual bool Execute(ResultSet& resultset);
			};
		}
	}
}

#endif