/*
 *  MatchSet.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/7/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

// grouping here is by sequence group by and the instantiated template values

/*
 * Sets of matches available in order by key
 */

#ifndef _flow_engine_match_set_h_
#define _flow_engine_match_set_h_

#include <Common.h>
#include <Engine/Sequential/Match.h>

namespace Flow {
  namespace Engine {
    class MatchSet {
    public:
      vector<size_t> keys; 
      map< size_t, vector<Sequential::Match> > matches;
      
      void insert(size_t key, Sequential::Match& match) {
        keys.push_back(key);
        matches[key].push_back(match);
      }
    };
  }
}

#endif