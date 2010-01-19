/*
 *  Base.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_query_executive_base_h_
#define _flow_engine_query_executive_base_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Query/Base.h>
#include <Engine/Executive/Constructor.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Executive {
			class Base {
			protected:
				Query::Base* query;
				Domain::Base* domain;
				
			public:
				Base(Domain::Base* domain, Query::Base* query) {
					this->domain = domain;
					this->query = query;
				}
				
				virtual bool Execute(Groups& results) = 0;
			};
		}
	}
}

#endif