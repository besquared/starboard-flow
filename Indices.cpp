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

bool Indices::Allocate(const map<string, string>& row) {
	if(!this->meta->OpenWriter()) { return false; }	

	set<string> dimensions;
	map<string, string>::const_iterator cell;
	for(cell = row.begin(); cell != row.end(); cell++) {
		dimensions.insert(cell->first);
	}

	if(!this->meta->Allocate(dimensions)) { return false; }
	
	this->meta->Close();
	
	return true;
}

bool Indices::Insert(const RecordID& record, const map<string, string>& row) {
	if(!this->Allocate(row)) { return false; }
	
	if(!this->meta->OpenReader()) { return false; }
	string name;
	map< string, vector<string> > indices;
	map<string, string>::const_iterator cell;
	for(cell = row.begin(); cell != row.end(); cell++) {
		if(this->meta->Index(cell->first, name)) {
			indices[name].push_back(cell->first);
		} else {
			this->meta->Close(); return false;
		}
	}
	this->meta->Close();
	
	if(!this->meta->index->OpenWriter()) { return false; }

	map<string, string> partition;
	vector<string>::iterator dimension;
	map< string, vector<string> >::iterator fragment;
	for(fragment = indices.begin(); fragment != indices.end(); fragment++) {
		for(dimension = fragment->second.begin(); dimension != fragment->second.end(); dimension++) {
			partition.clear();
			if((cell = row.find(*dimension)) != row.end()) {
				partition[*dimension].assign(cell->second);
			}
		}
		
		if(!this->meta->index->Insert(record, partition)) { 
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
}

// RecordMap map<string, RecordList>
// RecordTree map<string, ValueMap>
bool Indices::Lookup(const set<string>& dimensions,
										 const vector<Condition>& conditions, RecordTree& tree) {
	
	if(!this->meta->OpenReader()) { return false; }
	
	set<string>::iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		RecordMap records;
		
		
		
		tree[dimension] = records;
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
