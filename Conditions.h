/*
 *  Conditions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_conditions_h_
#define _flow_conditions_h_

#include <Common.h>
#include <Condition/Base.h>
#include <Condition/Eq.h>
#include <Condition/In.h>
#include <Condition/Gt.h>
#include <Condition/Gte.h>
#include <Condition/Lt.h>
#include <Condition/Lte.h>

using namespace std;
using namespace boost;
using namespace Flow;

namespace Flow {
  class Conditions : public vector< shared_ptr<Condition::Base> > {
  public:
		/*
		 * Shortcuts
		 */
		void Eq(const string& name, const string& value);
		void Gt(const string& name, const string& value);
		void Gte(const string& name, const string& value);
		void Lt(const string& name, const string& value);
		void Lte(const string& name, const string& value);
		void In(const string& name, const vector<string>& value);

		/*
		 * Application
		 */
		void Apply(const string& column, vector<string>& values) const;
  };
}

#endif