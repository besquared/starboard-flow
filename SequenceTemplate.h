/*
 *  SequenceTemplate.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Common.h"
#include "SequenceDimension.h"

namespace Flow {
	class SequenceTemplate : public vector< shared_ptr<SequenceDimension> > {
	public:
		enum Matching { SUBSTRING, FUNNEL };
		enum Restriction { LEFT_MATCH, LEFT_DATA, ALL_MATCH };
		
		Matching matching;
		Restriction restriction;
		
		SequenceTemplate();
		
		void push_back(const string& name, const string& symbol, const string& alias);
		void push_back(const string& name, const string& symbol, const string& alias, const shared_ptr<Conditions> conditions);
	};
}