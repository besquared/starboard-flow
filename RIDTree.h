/*
 *  RIDTree.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/19/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_rid_tree_h_
#define _flow_rid_tree_h_

#include "Common.h"
#include "RIDList.h"
#include "RIDMap.h"

namespace Flow {
	class RIDTree : public map<string, RIDMap> {
	public:
		void operator&(RIDList& records);
		void operator|(RIDList& records);
	};
}

#endif