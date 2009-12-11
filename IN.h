/*
 *  IN.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _in_included_
#define _in_included_

#include "Common.h"
#include "Condition.h"

namespace Flow {
  class IN : public Condition {
	public:
		vector<string> values;
		bool negation;
		
		IN(const string& column, const vector<string>& values);
		IN(const string& column, const vector<string>& values, bool negation);
		
		void Apply(vector<string>& values);
		void ApplyNegation(vector<string>& values);
	};
}

#endif