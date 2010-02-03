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
  map<string, string> tvalues;
//  cout << "Pattern has size " << m << endl;
  
  // TODO this doesn't match properly, it doesn't match 
  //  template variables to one another for example a pattern
  //  X,X,X should require that all three values be the same
  //  this requires some global pattern knowledge that individual
  //  dimension matchers need to be passed.
  
  // Keep a stack of the previous matches and pass it in perhaps?
  //  ahh we can keep a map of each template variable as we go along
  // X => 16th street, Y => Powell Street and each dimension knows what it
  // is so we when we match we can say, ok, it matches the conditions, now
  // lets additionally check to make sure the value matches the dictionary
  // value if there is one already.
  
  // This also answers our question as to how to pass back the matched tuples
  
  for(size_t i = 0; i < input.size(); i++) {
    Group& curr_group = input[i];
    size_t n = curr_group.records.size();
    
    // pattern is longer than text, no matches possible
    if(m > n) { continue; }
    
//    cout << "Scanning shifts up to " << n - m << endl;
    for(size_t s = 0; s <= n - m; s++) {
//      cout << "Starting scan at shift " << s << endl;
      size_t j = 1;
      
      // cout << "checking for a match in group " << i << " at position " << s << endl;
      // look at dimension 0 first, see if position 0 of text matches
      // if it does then increment j, look at position 1 of text
      // continue until it either matches or doesn't match, if it
//      cout << "Checking position " << s + j - 1 << endl;
      while(j <= m && pattern[j - 1]->match(curr_group, s + j - 1)) {
        // update our template pattern map
        cout << pattern[j - 1]->symbol << endl;
        cout << curr_group.dimensions[pattern[j - 1]->name][s] << endl;
//        tvalues[dim->symbol] = curr_group[dim->name][s + j - 1]
        // tvalues["X"] = "Montgomery";
        j++;
      }
      
      if(j > m) {
//        cout << "Inserting some new stuff" << endl;
        results[i].push_back(Match(s, tvalues));
      } else {
//        cout << "Broke out of the loop with j < m" << endl;
      }
      
      tvalues.clear();
    }
    // match not found in this group
  }
}