/*
 *  Condition.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _condition_included_
#define _condition_included_

#include "Common.h"

namespace Flow {
  class Condition {
	public:
		enum ConditionType { EQ, GT, GTE, LT, LTE, IN };

		string column;
		ConditionType type;
		
		Condition(const string& column) {
			this->column = column;
		}
		
		virtual void Apply(vector<string>& values) = 0;
	};
}

#endif