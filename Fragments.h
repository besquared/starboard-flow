/*
 *  Fragments.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/16/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _included_fragments_
#define _included_fragments_

#include "Common.h"
#include "Meta.h"
#include "Fragment.h"
#include "Condition.h"

namespace Flow {
	class Fragments {
		Meta* meta;
		
	public:
		Fragments(Meta* meta);
		
		bool Allocate(const map<string, string>& row);
		bool Insert(const RecordID& record, const map<string, string>& row);
		bool Lookup(const vector<string>& dimensions, const vector<Condition>& conditions);
	};
}

#endif