/*
 *  Indices.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/16/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Indices.h"

Domain::Indices::Indices() {}

Domain::Indices::Indices(Data::Meta *meta) {
	this->meta = meta;
}

Domain::Indices::~Indices() {}

bool Domain::Indices::Allocate(const Data::Record& record) {
	if(!this->meta->OpenWriter()) { return false; }	
	if(!this->meta->Allocate(record.Dimensions())) { return false; }
	this->meta->Close();
	return true;
}

bool Domain::Indices::Insert(const Data::Record& record) {
	if(!this->Allocate(record)) { return false; }
		
	if(!this->meta->OpenReader()) { return false; }
	string name;
	Data::Record::const_iterator cell;
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
	Data::Record partition;
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
bool Domain::Indices::Lookup(const ValueMap& specified, Data::RIDList& results) {
	if(!this->meta->OpenReader()) { return false; }	
	if(!this->meta->index->OpenReader()) { return false; }
	
	string name;
	ValueMap::const_iterator cell;
	map< string, set<string> > indices;
	for(cell = specified.begin(); cell != specified.end(); cell++) {
		if(this->meta->Index(cell->first, name)) {
			indices[name].insert(cell->first);
		} else {
			this->meta->Close(); return false;
		}
	}
	
	ValueMap partition;
	Data::RIDList records;
	map< string, set<string> >::iterator fragment;
	for(fragment = indices.begin(); fragment != indices.end(); fragment++) {
		partition.clear();
		this->Partition(specified, fragment->second, partition);
		if(!this->meta->index->Lookup(partition, records)) {
			this->meta->index->Close(); return false; 
		} else {
			if(records.size() == 0) {
				results.clear(); return true;
			} else {
				if(results.size() == 0) {
					results.assign(records.begin(), records.end());
				} else {
					results = results & records;
				}
			}
		}
	}
	this->meta->index->Close();
	this->meta->Close();
	return true;
}

// RIDMap map<string, RIDList>
// RIDTree map<string, ValueMap>
bool Domain::Indices::Lookup(const set<string>& dimensions,
														 const Conditions& conditions, 
														 Data::RIDTree& results) {
	
	ValuesMap values;
	if(!this->meta->index->OpenReader()) { return false; }
	if(!this->meta->index->Lookup(dimensions, values)) { 
		this->meta->index->Close(); return false; 
	}
	
	Data::RIDMap records;
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

void Domain::Indices::Partition(const ValueMap& specified, const set<string>& dimensions, ValueMap& results) {
	ValueMap::const_iterator element;
	for(element = specified.begin(); element != specified.end(); element++) {
		if(dimensions.find(element->first) != dimensions.end()) {
			results[element->first] = element->second;
		}
	}
}
