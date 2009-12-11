/*
 *  SequenceDimension.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Common.h"
#include "Conditions.h"

namespace Flow {
	class SequenceDimension {
	public:
		string name;
		string symbol;
		string alias;
		shared_ptr<Conditions> conditions;
		
		SequenceDimension(const string& name, const string& symbol, const string& alias);
		SequenceDimension(const string& name, const string& symbol, const string& alias, const shared_ptr<Conditions>& conditions);
	};
}