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

void Scanner::Substring::execute(Pattern& pattern, vector<WorkSet>& sequences, Matches& results) {
  size_t pat_length = pattern.size();
  
  for(size_t i = 0; i < sequences.size(); i++) {
    WorkSet& cseq = sequences[i];
    size_t seq_length = cseq.records.size();
    
    if(pat_length > seq_length) { continue; }
    
    for(size_t shft = 0; shft <= seq_length - pat_length; shft++) {
      Match cmatch(shft);
      if(pattern.match(cseq, cmatch)) {
        // if all match
        // shft += pat_length - 1;
        // if left match
        // break;
        results[i].push_back(cmatch);
      }
    }
  }
}