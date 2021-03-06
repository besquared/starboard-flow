/*
 *  In.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_condition_in_h_
#define _flow_condition_in_h_

#include <Common.h>

#include "Base.h"

namespace Flow {
	namespace Condition {
		class In : public Condition::Base {
		public:
			vector<string> values;
			bool negation;
			
			In(const string& column, const vector<string>& values) :
			Condition::Base::Base(column) {
				this->values = values;
				this->negation = false;
				this->type = Condition::Base::IN;
			}
			
			In(const string& column, const vector<string>& values, bool negation)  :
			Condition::Base::Base(column) {
				this->values = values;
				this->negation = negation;
				this->type = Condition::Base::IN;
			}			
			
      bool Check(string& value) {
        vector<string>::iterator found;
        found = find(values.begin(), values.end(), value);
        
        if(found == this->values.end()) {
          return false;
        } else {
          return true;
        }
      }
      
			void Apply(vector<string>& values) {
				vector<string> intersected;
				set_intersection(values.begin(), values.end(), this->values.begin(), this->values.end(), back_inserter(intersected));
				values = intersected;
			}
			
			void ApplyNegation(vector<string>& values) {
				vector<string> differenced;
				set_difference(values.begin(), values.end(), this->values.begin(), this->values.end(), back_inserter(differenced));
				values = differenced;
			}
      
      void print(ostream& out) const {
        out << column << " IN (";
        for(size_t i = 0; i < values.size(); i++) {
          out << values[i];
          if(i < values.size() - 1) out << ", "; 
        }
        out << ")";
      }
		};
	}
}

#endif