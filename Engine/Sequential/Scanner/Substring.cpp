/*
 *  Substring.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/29/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Substring.h"

using namespace Engine::Sequential;

Scanner::Substring::Substring() : Scanner::Base::Base() {
  
}

Scanner::Substring::~Substring() {

}

void Scanner::Substring::execute(Pattern& pattern, Groups& input, Matches& results) {
  size_t m = pattern.size();
  
  for(size_t i = 0; i < input.size(); i++) {
    Group& current_group = input[i];
    size_t n = current_group.records.size();
    
    if(m > n) { continue; }
    
    for(size_t s = 0; s <= n - m; s++) {
      size_t j = 1;
      Match current_match(s);

      while(j <= m && pattern[j - 1]->match(current_group, s + j - 1, current_match)) {
        j++;
      }
      
      if(j > m) {
        results[i].push_back(current_match);
      }
    }
  }
}