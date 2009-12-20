/*
 *  RIDList.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_rid_list_h_
#define _flow_rid_list_h_

#include "Common.h"

namespace Flow {
	class RIDList : public vector<RecordID> {
	public:
		RIDList();
		RIDList(void* buffer, int bsize);
		RIDList(RecordID* buffer, size_t count);
		
		RIDList operator&(RIDList& other);
		RIDList operator|(RIDList& other);
	};
}

#endif