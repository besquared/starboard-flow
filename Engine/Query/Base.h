/*
 *  Base.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_query_base_h_
#define _flow_engine_query_base_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Groups.h>
#include <Engine/Executive/Base.h>

using namespace std;
using namespace Flow;
using namespace Flow::Domain;

namespace Flow {
	namespace Engine {
		namespace Query {
			class Base {
			public:
				Query();
				virtual ~Query();
				virtual bool Execute(Domain::Base* domain, Groups& results) = 0;
				virtual bool Execute(Executive::Base& executive, Groups& results) = 0;
			};
		}
	}
}