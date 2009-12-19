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
	set<string> dimensions;
	map<string, string>::const_iterator cell;
	
	for(cell = row.begin(); cell != row.end(); cell++) {
		dimensions.insert(cell->first);
	}

	if(!this->meta->Allocate(dimensions)) {
		return false;
	} else {
		return true;
	}
}

bool Indices::Insert(const RecordID& record, const map<string, string>& row) {
	if(!this->meta->OpenWriter()) {
		return false;
	}	
		
	if(!this->Allocate(row)) {
		return false;
	}

	string name;
	map< string, vector<string> > indices;
	map<string, string>::const_iterator cell;
	for(cell = row.begin(); cell != row.end(); cell++) {
		if(this->meta->Fragment(cell->first, name)) {
			indices[name].push_back(cell->first);
		} else {
			return false;
		}
	}
	
	this->meta->Close();
	
	map<string, string> partition;
	vector<string>::iterator dimension;
	map< string, vector<string> >::iterator fragment;
	for(fragment = indices.begin(); fragment != indices.end(); fragment++) {
		for(dimension = fragment->second.begin(); dimension != fragment->second.end(); dimension++) {
			cell = row.find(*dimension);
			if(cell != row.end()) {
				partition[*dimension].assign(cell->second);
			}
		}

		Fragment index = this->meta->GetIndex();
		
		if(index.OpenWriter()) {
			if(index.Insert(record, partition)) {
				index.Close();
			} else {
				index.Close();
				return false;
			}
		} else {
			return false;
		}
		
		partition.clear();
	}
	
	return true;
}

bool Indices::Lookup(const vector<string>& dimensions, const vector<Condition>& conditions) {
	return true;
}
