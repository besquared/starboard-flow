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

void Scanner::Substring::execute(Pattern& pattern, Groups& sequences, Matches& results) {
  size_t pat_length = pattern.size();
  
  for(size_t i = 0; i < sequences.size(); i++) {
    Group& current_seq = sequences[i];
    size_t seq_length = current_seq.records.size();
    
    if(pat_length > seq_length) { continue; }
    
    for(size_t s = 0; s <= seq_length - pat_length; s++) {
      size_t j = 1;

      Match current_match(s);
      while(j <= pat_length && pattern[j - 1]->match(current_seq, current_match, s + j - 1)) {
        j++;
      }
      
      if(j > pat_length) {
        results[i].push_back(current_match);
      }
    }
  }
}