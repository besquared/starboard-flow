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
	this->buffer = NULL;
	this->clear();
}

RecordList::RecordList(void* buffer, int bsize) {
	this->assign(buffer, bsize);
}

RecordList::RecordList(RecordID* buffer, size_t count) {
	this->assign(buffer, count);
}

RecordList::~RecordList() {
	free(this->buffer);
}

size_t RecordList::size() {
	return this->_size;	
}

size_t RecordList::capacity() {
	return this->_capacity;
}

void RecordList::reserve(size_t size) {
	if(size > this->_capacity) {
		size_t nsize = size * sizeof(RecordID);
		
		this->_capacity = size;
		this->buffer = (RecordID*)realloc(this->buffer, nsize);
	}
}

void RecordList::push_back(RecordID value) {
	if(this->_size == this->_capacity) {
		this->reserve(this->_capacity * 2);
	}
	
	*(buffer + this->_size) = value;
	this->_size++;
}

void RecordList::assign(void* buffer, int bsize) {
	this->clear();
	
	this->buffer = (RecordID*)realloc(this->buffer, bsize);
	memcpy(this->buffer, buffer, bsize);
	
	this->_size = bsize / sizeof(RecordID);
	this->_capacity = this->_size;	
}

void RecordList::assign(RecordID* buffer, size_t count) {
	this->clear();
	
	size_t bsize = count * sizeof(RecordID);
	this->buffer = (RecordID*)realloc(this->buffer, bsize);
	memcpy(this->buffer, buffer, bsize);
	
	this->_size = count;
	this->_capacity = this->_size;
}

void RecordList::clear() {
	if(this->buffer != NULL) { free(this->buffer); }
	
	this->_size = 0;
	this->_capacity = 4;
	this->allocate(this->_capacity);	
}

RecordID RecordList::at(size_t offset) {
	return *(buffer + offset);
}

RecordID RecordList::operator[](size_t offset) {
	return *(buffer + offset);
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

/*
 * Protected
 */

void RecordList::allocate(int size) {
	size_t nsize = 4 * sizeof(RecordID);
	this->buffer = (RecordID*)malloc(nsize);
}
