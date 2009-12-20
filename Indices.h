/*
 *  Indices.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/16/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_indices_h_
#define _flow_indices_h_

#include "Common.h"
#include "Meta.h"
#include "Index.h"
#include "Condition.h"

#include "Record.h"
#include "RIDList.h"
#include "RIDMap.h"
#include "RIDTree.h"

namespace Flow {
	class Indices {
	protected:
		Meta* meta;
		bool Allocate(const Record& record);

	public:
		Indices(Meta* meta);
		
		bool Insert(const Record& record);
		bool Lookup(const ValueMap& specified);
		bool Lookup(const set<string>& dimensions, const vector<Condition>& conditions, RIDTree& results);
	};
}

#endif