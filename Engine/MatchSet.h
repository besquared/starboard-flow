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
    class Matching {
    public: 
      map<string, string> values;
      vector<Sequential::Match> matches;
      
      Matching() {}
      Matching(const map<string, string>& values) {
        this->values = values;
      }
      
      friend ostream& operator<<(ostream& out, const Matching& matching) {
        out << "{";
        
        size_t i = 0;
        map<string, string>::const_iterator value;
        for(value = matching.values.begin(); value != matching.values.end(); value++, i++) {
          out << value->first << " => " << value->second;
          if(i < matching.values.size() - 1) out << ", "; 
        }
        
        out << "}";
        return out;
      }      
    };
    
    class MatchSet {
    public:
      vector<size_t> keys; 
      map<size_t, Matching> matchings;

      void insert(map<string, string>& grouping, Sequential::Match& match) {
        size_t hshkey = 0;
        map<string, string>::iterator keypart;
        boost::hash_range(hshkey, grouping.begin(), grouping.end());
        
        if(matchings.count(hshkey) == 0) {
          keys.push_back(hshkey);
          matchings[hshkey] = Matching(grouping);
        }
        
        matchings[hshkey].matches.push_back(match);
      }
      
      Matching& operator[](const size_t key) {
        return this->matchings[key];
      }
    };
  }
}

#endif