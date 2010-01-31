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

void Scanner::Substring::execute(Groups& input, Matches& results) {
  for(size_t i = 0; i < input.size(); i++) {
    size_t n = input[i].size();
    size_t m = pattern.size();
    for(size_t s = 0; s < n - m; s++) {
      size_t j = 1;
      
      while(j <= m && pattern[j]->match(input[i], s + j)) 
        j++;
      
      if(j > m)
        results.insert(i, s);
    }
    // match not found in this group
  }
}