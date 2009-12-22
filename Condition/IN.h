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

#include "Common.h"
#include "Condition/Base.h"

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
			
			void Apply(vector<string>& values) {
				values = Common::Intersect(values, this->values);
			}
			
			void ApplyNegation(vector<string>& values) {
				// THIS DOESN'T WORK YET use stl
				values = Common::Difference(values, this->values);
			}
		};
	}
}

#endif