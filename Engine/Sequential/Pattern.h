/*
 *  Pattern.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_pattern_h_
#define _flow_engine_sequential_pattern_h_

#include <Common.h>
#include <Engine/WorkSet.h>

#include "Dimension.h"

namespace Flow {
	namespace Engine {
		namespace Sequential {      
      using namespace std;
      
			class Pattern : public vector< boost::shared_ptr<Sequential::Dimension> > {
			public:
				enum Matching { SUBSTRING, REGEX };
				enum Restriction { LEFT_MATCH, ALL_MATCH, LEFT_DATA };
				
				Matching matching;
				Restriction restriction;
				
				Pattern();
				
				void push_back(const string& name, const string& symbol, const string& alias);
				void push_back(const string& name, const string& symbol, const string& alias, const Conditions& conditions);
        
        set<string> dimensions();
        bool match(WorkSet& sequence, Match& result);
			};
		}
	}
}

#endif