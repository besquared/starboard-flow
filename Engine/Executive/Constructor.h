/*
 *  Constructor.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_executive_constructor_h_
#define _flow_engine_executive_constructor_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Query/Base.h>

using namespace std;
using namespace Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Executive {		
			class Constructor {				
			public:
				bool Execute(Domain::Base* domain, Query::Base* query, Groups& results);
				
			protected:
				void Construct(vector<string>& instantiated_vals, RIDList& instantiated, 
											 vector<string>& inquired_dims, RIDTree& inquired, Groups& results);
				void Construct(vector<string>& instantiated_vals, RIDList& instantiated, 
											 vector<string>& inquired_dims, RIDTree& inquired, int offset, 
											 vector<string>& values, RIDList& records, Groups& results);				
				
			};
		}
	}
}

#endif
