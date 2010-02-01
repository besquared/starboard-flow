/*
 *  Condition.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_condition_base_h_
#define _flow_engine_condition_base_h_

#include <Common.h>

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Condition {
		class Base {
		public:
			enum ConditionType { EQ, GT, GTE, LT, LTE, IN };

			string column;
			ConditionType type;
			
			Base(const string& column) {
				this->column = column;
			}
			
      virtual bool Check(string& value) = 0;
			virtual void Apply(vector<string>& values) = 0;
		};
	}
}

#endif