/*
 *  Sequential.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_executive_sequential_h_
#define _flow_engine_executive_sequential_h_

#include "Base.h"
#include <Engine/Query/Sequential.h>
#include <Engine/Pipeline/Constructor.h>
#include <Engine/Pipeline/Gatherer.h>
#include <Engine/Pipeline/Scanner.h>
#include <Engine/Pipeline/Aggregator.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Executive {
			class Sequential : public Executive::Base {
			protected:
        Query::Sequential* query;
        
				Pipeline::Constructor* constructor;
				Pipeline::Gatherer* gatherer;
        Pipeline::Scanner* scanner;
				Pipeline::Aggregator* aggregator;
				
			public:
				Sequential(Domain::Base* domain, Query::Sequential* query);
				virtual ~Sequential();
				
				virtual bool Execute(ResultSet& results);
			};
		}
	}
}

#endif