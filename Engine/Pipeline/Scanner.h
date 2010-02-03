/*
 *  Scanner.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_pipeline_scanner_h_
#define _flow_engine_pipeline_scanner_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Query/Sequential.h>
#include <Engine/Sequential/Scanner/Match.h>
#include <Engine/Sequential/Scanner/Substring.h>

using namespace std;
using namespace Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Pipeline {		
			class Scanner {				
			public:
				bool Execute(Domain::Base* domain, Query::Sequential* query, Groups& results);				
			};
		}
	}
}

#endif
