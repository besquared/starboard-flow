/*
 *  Matches.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/31/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * An index into a set of groups that defines scanned matches
 */

#ifndef _flow_engine_sequential_scanner_matches_h_
#define _flow_engine_sequential_scanner_matches_h_

#include <Common.h>
#include <Engine/Groups.h>

namespace Flow {
	namespace Engine {		
		namespace Sequential {
      namespace Scanner {
        class Matches {
        protected:
          map< size_t, vector<size_t> > matches_;
        public:
          Matches(){}
          
          vector<size_t>& at(size_t group) {
            return matches_[group];
          }
          
          void insert(size_t group, size_t index) {
            matches_[group].push_back(index);
          }
        };
      }
		}
	}
}

#endif