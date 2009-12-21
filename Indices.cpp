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
										 const Conditions& conditions, RIDTree& results) {
	
	ValuesMap values;
	if(!this->meta->index->OpenReader()) { return false; }
	if(!this->meta->index->Lookup(dimensions, values)) { 
		this->meta->index->Close();return false; 
	}
	
	RIDMap records;
	ValuesMap::iterator vlist;
	for(vlist = values.begin(); vlist != values.end(); vlist++) {
		sort(vlist->second.begin(), vlist->second.end());
		conditions.Apply(vlist->first, vlist->second);
				
		if(!this->meta->index->Lookup(vlist->first, vlist->second, records)) { 
			this->meta->index->Close();
			return false;
		} else {
			results[vlist->first] = records;
		}
	}
	
	this->meta->index->Close();
	
	return true;
}
