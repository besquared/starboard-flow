/*
 *  Conditions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _conditions_included_
#define _conditions_included_

#include "Common.h"
#include "Condition.h"

#include "EQ.h"
#include "IN.h"
#include "GT.h"
#include "GTE.h"
#include "LT.h"
#include "LTE.h"

namespace Flow {
  class Conditions : public vector< shared_ptr<Condition> > {
  public:
		/*
		 * Shortcuts
		 */
		void eq(const string& name, const string& value);
		void gt(const string& name, const string& value);
		void gte(const string& name, const string& value);
		void lt(const string& name, const string& value);
		void lte(const string& name, const string& value);
		void in(const string& name, const vector<string>& value);

		/*
		 * Application
		 */
		void Apply(const string& column, vector<string>& values);
  };
}

#endif