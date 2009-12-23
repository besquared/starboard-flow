/*
 *  SequenceTemplate.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_template_h_
#define _flow_engine_sequential_template_h_

#include <Common.h>
#include "Dimension.h"

namespace Flow {
	class SequenceTemplate : public vector< shared_ptr<SequenceDimension> > {
	public:
		enum Matching { SUBSTRING, FUNNEL, CONVERSION };
		enum Restriction { LEFT_MATCH, LEFT_DATA, ALL_MATCH };
		
		Matching matching;
		Restriction restriction;
		
		SequenceTemplate();
		
		void push_back(const string& name, const string& symbol, const string& alias);
		void push_back(const string& name, const string& symbol, const string& alias, const shared_ptr<Conditions> conditions);
	};
}

#endif