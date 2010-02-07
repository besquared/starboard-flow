/*
 *  Constructor.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_pipeline_constructor_h_
#define _flow_engine_pipeline_constructor_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/WorkSet.h>
#include <Engine/Query/Base.h>

using namespace std;
using namespace Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Pipeline {		
			class Constructor {				
			public:
				virtual bool Execute(Domain::Base* domain, Query::Base* query, Groups& results);
				
			protected:
				virtual void Construct(vector<string>& instantiated_vals, RIDList& instantiated, 
											 vector<string>& inquired_dims, RIDTree& inquired, Groups& results);
				virtual void Construct(vector<string>& instantiated_vals, RIDList& instantiated, 
											 vector<string>& inquired_dims, RIDTree& inquired, int offset, 
											 vector<string>& values, RIDList& records, Groups& results);				
				
			};
		}
	}
}

#endif
