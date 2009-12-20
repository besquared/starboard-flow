/*
 *  RIDList.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "RIDList.h"

RIDList::RIDList() {}

RIDList::RIDList(void* buffer, int bsize) {
//	this->assign(buffer, bsize);
}

RIDList::RIDList(RecordID* buffer, size_t count) {
//	this->assign(buffer, count);
}

// Performs an AND operation on two sorted RecordLists
RIDList RIDList::operator&(RIDList& other) {
	RIDList results;
	results.reserve(min<size_t>(this->size(), other.size()));
	set_intersection(this->begin(), this->end(), other.begin(), other.end(), back_inserter(results));
	return results;
}

// Performs an OR on two sorted RecordLists
//  If lists are partitioned this is equivalent to a merge
RIDList RIDList::operator|(RIDList& other) {
	RIDList results;
	results.reserve(this->size() + other.size());
	merge(this->begin(), this->end(), other.begin(), other.end(), results.begin());
	return results;
}