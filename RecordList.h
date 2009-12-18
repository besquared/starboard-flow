/*
 *  RecordList.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _included_record_list_
#define _included_record_list_

#include "Common.h"

class RecordList : public vector<RecordID> {
public:
	RecordList();
  RecordList(void* buffer, int bsize);
  RecordList(RecordID* buffer, size_t count);
  
	RecordList operator&(RecordList& other);
	RecordList operator|(RecordList& other);
};

#endif