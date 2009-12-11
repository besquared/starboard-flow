/*
 *  EQ.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _eq_included_
#define _eq_included_

#include "Common.h"
#include "Condition.h"

namespace Flow {
  class EQ : public Condition {
	public:
		string value;
		bool negation;
		
		EQ(const string& column, const string& value);
		EQ(const string& column, const string& value, bool negation);
		
		void Apply(vector<string>& values);
		void ApplyNegation(vector<string>& values);
	};
}

#endif