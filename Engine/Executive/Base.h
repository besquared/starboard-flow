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
#include <Engine/WorkSet.h>
#include <Engine/ResultSet.h>
#include <Engine/Query/Base.h>

namespace Flow {
	namespace Engine {		
		namespace Executive {
			class Base {
			protected:
				Domain::Base* domain;
				
			public:
				Base(Domain::Base* domain) {
					this->domain = domain;
				}
			};
		}
	}
}

#endif