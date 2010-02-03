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
    Group& cseq = sequences[i];
    size_t seq_length = cseq.records.size();
    
    if(pat_length > seq_length) { continue; }
    
    for(size_t shft = 0; shft <= seq_length - pat_length; shft++) {
      size_t offset = 1;

      Match cmatch(shft);
      while(offset <= pat_length && pattern[offset - 1]->match(cseq, cmatch, shft + offset - 1)) {
        offset++;
      }
      
      if(offset > pat_length) {
        results[i].push_back(cmatch);
      }
    }
  }
}