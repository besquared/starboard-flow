/*
 *  EQ.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_condition_eq_h_
#define _flow_condition_eq_h_

#include <Common.h>
#include "Condition/Base.h"

namespace Flow {
	namespace Condition {
		class Eq : public Condition::Base {
		public:
			string value;
			bool negation;
			
			Eq(const string& column, const string& value)  :
			Condition::Base::Base(column) {
				this->value = value;
				this->negation = false;
				this->type = Condition::Base::EQ;
			}
			
			Eq(const string& column, const string& value, bool negation) :
			Condition::Base::Base(column) {
				this->value = value;
				this->negation = negation;
				this->type = Condition::Base::EQ;
			}
			
			void Apply(vector<string>& values)  {
				if(this->negation) {
					this->ApplyNegation(values);
				} else {
					vector<string> results;
					results.reserve(values.size());
					size_t vsize = values.size();
					for(size_t i = 0; i < vsize; i++) {
						if(values[i] == this->value) {
							results.push_back(values[i]);
						}
					}
					values = results;
				}
			}
			
			void ApplyNegation(vector<string>& values)  {
				vector<string> results;
				results.reserve(values.size());
				size_t vsize = values.size();
				for(size_t i = 0; i < vsize; i++) {
					if(values[i] != this->value) {
						results.push_back(values[i]);
					}
				}
				values = results;
			}			
		};
	}
}

#endif