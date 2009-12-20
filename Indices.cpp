/*
 *  Indices.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/16/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Indices.h"

Indices::Indices(Meta *meta) {
	this->meta = meta;
}

bool Indices::Allocate(const Record& record) {
	if(!this->meta->OpenWriter()) { return false; }	
	if(!this->meta->Allocate(record.Dimensions())) { return false; }
	this->meta->Close();
	return true;
}

bool Indices::Insert(const Record& record) {
	if(!this->Allocate(record)) { return false; }
	
	// Collect fragment membership
	
	if(!this->meta->OpenReader()) { return false; }
	string name;
	Record::const_iterator cell;
	map< string, set<string> > indices;
	for(cell = record.begin(); cell != record.end(); cell++) {
		if(this->meta->Index(cell->first, name)) {
			indices[name].insert(cell->first);
		} else {
			this->meta->Close(); return false;
		}
	}
	this->meta->Close();
	
	// Insert each fragment partition into the index
	
	if(!this->meta->index->OpenWriter()) { return false; }

	Record partition;
	vector<string>::iterator dimension;
	map< string, set<string> >::iterator fragment;
	for(fragment = indices.begin(); fragment != indices.end(); fragment++) {
		partition = record.Partition(fragment->second);
		if(!this->meta->index->Insert(partition)) {
			this->meta->index->Close(); return false; 
		}
	}
	this->meta->index->Close();

	return true;
}

// ValueMap map<string, string>
bool Indices::Lookup(const ValueMap& specified) {
	if(!this->meta->OpenReader()) { return false; }
	this->meta->Close();
	return true;
}

// RIDMap map<string, RIDList>
// RIDTree map<string, ValueMap>
bool Indices::Lookup(const set<string>& dimensions,
										 const vector<Condition>& conditions, RIDTree& results) {
	
	if(!this->meta->OpenReader()) { return false; }
	
	set<string>::iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		RIDMap records;
		
		results[*dimension] = records;
	}
	
//	for(size_t i = 0; i < dimensions.size(); i++) {
//    InquiredDimension dimension;
//    
//    string fragment = this->dimensions->Fragment(dimensions[i]);
//    vector<string> values = this->dimensions->Values(dimensions[i]);
//		
//		sort(values.begin(), values.end());
//		
//		conditions.Apply(dimensions[i], values);
//		// Run values through a set of conditional filters here
//		
//    for(int j = 0; j < values.size(); j++) {
//      dimension[values[j]] = this->database->GetRecordIdList(
//																														 this->IndexKey(fragment, this->Component(dimensions[i], values[j]))
//																														 );
//    }
//    
//    results[dimensions[i]] = dimension;
//  }	
	
	return true;
}
