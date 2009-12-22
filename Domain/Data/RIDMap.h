/*
 *  RIDMap.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/19/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_rid_map_h_
#define _flow_rid_map_h_

#include "Common.h"
#include "RIDList.h"

namespace Flow {
	class RIDMap : public map<string, RIDList> {
	public:
		void operator&(RIDList& records);
		void operator|(RIDList& records);
	};
}

#endif