/*
 *  Dimension.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_dimension_h_
#define _flow_engine_sequential_dimension_h_

#include <Common.h>
#include <Conditions.h>
#include <Engine/Group.h>

using namespace std;

namespace Flow {
	namespace Engine {
		namespace Sequential {
			class Dimension {
			public:
				string name;
				string symbol;
				string alias;
				Conditions conditions;
				
				Dimension(const string& name, const string& symbol, const string& alias);
				Dimension(const string& name, const string& symbol, const string& alias, const Conditions& conditions);
        
        // make sure that we don't read past end of group
        bool match(Group& haystack, size_t position);
			};
		}
	}
}

#endif