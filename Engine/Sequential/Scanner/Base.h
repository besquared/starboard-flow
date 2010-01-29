/*
 *  Base.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/29/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_scanner_base_h_
#define _flow_engine_sequential_scanner_base_h_

#include <Common.h>
#include <Engine/Groups.h>

namespace Flow {
	namespace Engine {		
		namespace Sequential {
      namespace Scanner {
        class Base {
        public:
          Base() {}
          virtual ~Base() {}
          virtual bool Execute(Groups& input, Groups& results) = 0;
        };
      }
		}
	}
}

#endif