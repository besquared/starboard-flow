/*
 *  LTE.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _lte_included_
#define _lte_included_

#include "Common.h"
#include "Condition.h"

namespace Flow {
  class LTE : public Condition {
	public:
		string value;
		
		LTE(const string& column, const string& value);
		
		void Apply(vector<string>& values);
	};
}

#endif