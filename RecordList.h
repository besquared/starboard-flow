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

class RecordList {
public:
  size_t _size;
  size_t _capacity;
  RecordID* buffer;
  
  RecordList();
  RecordList(void* buffer, int bsize);
  RecordList(RecordID* buffer, size_t count);
	~RecordList();
  
	size_t size();  
  size_t capacity();
  void reserve(size_t size);
	
  void push_back(RecordID value);
  void assign(void* buffer, int bsize);
	void assign(RecordID* buffer, size_t count);
	void clear();
	
  RecordID at(size_t offset);
  RecordID operator[](size_t offset);
  
	RecordList operator&(RecordList& other);
	RecordList operator|(RecordList& other);
	
protected:
  void allocate(int size);
};

#endif