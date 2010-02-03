/*
 *  Nneq.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_condition_neq_h_
#define _flow_condition_neq_h_

#include <Common.h>

#include "Base.h"

namespace Flow {
	namespace Condition {
		class Neq : public Condition::Base {
		public:
			string value;
			
			Neq(const string& column, const string& value)  :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::EQ;
			}
						
      bool Check(string& value) {
        return value != this->value;
      }
      
			void Apply(vector<string>& values)  {
        vector<string> results;
        results.reserve(values.size());
        size_t vsize = values.size();
        for(size_t i = 0; i < vsize; i++) {
          if(this->Check(values[i])) {
            results.push_back(values[i]);
          }
        }
        values = results;
			}
      
      void print(ostream& out) const {
        out << column << " != " << value;
      }      
		};
	}
}

#endif