/*
 *  Base.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_executive_base_h_
#define _flow_engine_executive_base_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>

namespace Flow {
	namespace Engine {
		namespace Query {
			class Base;
		}
		
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