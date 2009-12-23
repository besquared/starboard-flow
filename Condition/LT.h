/*
 *  Lt.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_condition_lt_h_
#define _flow_condition_lt_h_

#include <Common.h>
#include "Condition/Base.h"

namespace Flow {
	namespace Condition {
		class Lt : public Condition::Base {
		public:
			string value;
			
			Lt(const string& column, const string& value) :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::LT;
			}			
			
			void Apply(vector<string>& values) {
				vector<string> results;
				results.reserve(values.size());
				size_t vsize = values.size();
				for(size_t i = 0; i < vsize; i++) {
					if(values[i] < this->value) {
						results.push_back(values[i]);
					}
				}
				values = results;
			}
		};
	}
}

#endif