/*
 *  Base.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_aggregates_base_h_
#define _flow_aggregates_base_h_

#include <Common.h>
#include <Engine/Table.h>
#include <Engine/Column/TColumn.h>
#include <Engine/Column/TListColumn.h>

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		namespace Aggregate {
			class Base {
			public:
				vector<string> measures;
				
				Base(const string& measure);
				Base(const vector<string>& measure);
				virtual void Apply(Table& base) = 0;		
			};
		}
	}
}

#endif