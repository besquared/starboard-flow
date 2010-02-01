/*
 *  Substring.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/29/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * Naive Scanner for substring sequences
 */

#ifndef _flow_engine_sequential_scanner_substring_h_
#define _flow_engine_sequential_scanner_substring_h_

#include <Common.h>
#include <Engine/Groups.h>

#include "Base.h"

namespace Flow {
	namespace Engine {		
		namespace Sequential {
      namespace Scanner {
        class Substring : public Base {
        public:
          Substring();
          virtual ~Substring();
          virtual void execute(Pattern& pattern, Groups& input, Matches& results);
        };
      }
		}
	}
}

#endif