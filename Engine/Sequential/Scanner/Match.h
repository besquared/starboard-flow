/*
 *  Match.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/2/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_scanner_match_h_
#define _flow_engine_sequential_scanner_match_h_

#include <Common.h>

namespace Flow {
	namespace Engine {		
		namespace Sequential {
      namespace Scanner {        
        class Match {
        public:
          size_t position;
          map<string, string> tvalues;

          Match(size_t position, map<string, string>& tvalues) {
            this->position = position;
            this->tvalues = tvalues;
          }
        };
        
        typedef map< size_t, vector<Match> > Matches;
      }
		}
	}
}

#endif