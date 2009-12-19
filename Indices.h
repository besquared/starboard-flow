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
#include "Fragment.h"
#include "Condition.h"

namespace Flow {
	class Indices {
		Meta* meta;
		
	public:
		Indices(Meta* meta);
		
		bool Allocate(const map<string, string>& row);
		bool Insert(const RecordID& record, const map<string, string>& row);
		bool Lookup(const vector<string>& dimensions, const vector<Condition>& conditions);
	};
}

#endif