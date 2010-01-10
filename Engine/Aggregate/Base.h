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
#include <Engine/Groups.h>
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
				enum AggregateType { SINGLE, MULTI };
	
			protected:
				string alias_;
				string measure;
				vector<string> measures;
				AggregateType type;
				
			public:
				Base();
				Base(const string& measure);
				Base(const string& measure, const string& alias);
				Base(const vector<string>& measure, const string& alias);
				
				virtual string alias() = 0;
				virtual void apply(Groups& base) = 0;
				
				void measure_names(set<string>& results);
			};
		}
	}
}

#endif