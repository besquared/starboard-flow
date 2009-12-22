/*
 *  Record.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_record_h_
#define _flow_record_h_

#include "Common.h"

namespace Flow {
	class Record : public map<string, string> {
	public:
		RecordID id;
		
		Record();
		Record(RecordID id);

		set<string> Dimensions() const;
		vector<string> Values() const;
		Record Partition(const set<string>& dimensions) const;
	};
}

#endif