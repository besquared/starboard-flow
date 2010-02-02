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
  
  cout << "Pattern has size " << m << endl;
  
  for(size_t i = 0; i < input.size(); i++) {
    size_t n = input[i].records.size();
    
    // pattern is longer than text, no matches possible
    if(m > n) { 
      continue;
    }
    
    for(size_t s = 0; s <= n - m; s++) {
      size_t j = 1;
      
//      cout << "checking for a match in group " << i << " at position " << s << endl;
      // look at dimension 0 first, see if position 0 of text matches
      // if it does then increment j, look at position 1 of text
      // continue until it either matches or doesn't match, if it
      while(j <= m && pattern[j - 1]->match(input[i], s + j - 1)) {
        j++;
      }
      
      if(j > m) {
        results[i].push_back(s);
      }
    }
    // match not found in this group
  }
}