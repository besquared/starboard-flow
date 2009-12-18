/*
 *  RecordList.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "RecordList.h"

RecordList::RecordList() {
}

RecordList::RecordList(void* buffer, int bsize) {
//	this->assign(buffer, bsize);
}

RecordList::RecordList(RecordID* buffer, size_t count) {
//	this->assign(buffer, count);
}

// Performs an AND operation on two sorted RecordLists
RecordList RecordList::operator&(RecordList& other) {
	RecordList results;
	
	if(this->size() == 0 || other.size() ==0) {
		return results;
	} else {
		results.reserve(min<size_t>(this->size(), other.size()));
	}
	
	int aindex = 0; int bindex = 0;
	int alength = this->size(); int blength = other.size();
	
	RecordID avalue;
	RecordID bvalue;
	while(aindex < alength && bindex < blength) {
		avalue = (*this)[aindex];
		bvalue = other[bindex];
		
		if(avalue == bvalue) {
			results.push_back(avalue);
			aindex++; bindex++;  
		} else if(avalue < bvalue) {  
			aindex++;  
		} else { // avalue > bvalue
			bindex++;  
		}
	}
	
	return results;
}

// Performs an OR on two sorted RecordLists
//  If lists are partitioned this is equivalent to a merge
RecordList RecordList::operator|(RecordList& other) {
	RecordList results;
	results.reserve(this->size() + other.size());
	
	size_t aindex = 0; size_t bindex = 0;
	size_t alength = this->size(); size_t blength = other.size();
	
	RecordID avalue;
	RecordID bvalue;
	while(aindex < alength || bindex < blength) {
		avalue = (*this)[aindex];
		bvalue = other[bindex];
		
		if(aindex > alength) {
			results.push_back(bvalue);
			bindex++;
		} else if(bindex > blength) {
			results.push_back(avalue);
			aindex++;
		} else {
			if(avalue < bvalue) {
				results.push_back(avalue);
				aindex++;
			} else if(avalue > bvalue) {
				results.push_back(bvalue);
				bindex++;  
			} else { // avalue == bvalue
				results.push_back(avalue);
				aindex++; bindex++;
			}
		}
	}
	
	return results;
}