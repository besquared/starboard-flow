/*
 *  Fragments.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/16/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Fragments.h"

Fragments::Fragments(Master *master) {
	this->master = master;
}

bool Fragments::Insert(const RecordID& record, const map<string, string>& row) {
	master->OpenReader();
	
	string name;
	map< string, vector<string> > fragments;
	map<string, string>::const_iterator cell;
	for(cell = row.begin(); cell != row.end(); cell++) {
		if(master->Fragment(cell->first, name)) {
			fragments[name].push_back(cell->first);
		} else {
			return false;
		}
	}
	
	master->Close();
	
	map<string, string> partition;
	vector<string>::iterator dimension;
	map< string, vector<string> >::iterator fragment;
	for(fragment = fragments.begin(); fragment != fragments.end(); fragment++) {
		for(dimension = fragment->second.begin(); dimension != fragment->second.end(); dimension++) {
			partition[*dimension] = row[*dimension];
		}

		Fragment fragment = this->master->fragments->Get(cell->first);
		if(fragment.OpenWriter()) {
			if(fragment.Insert(record, partition)) {
				fragment.Close();
			} else {
				fragment.Close();
				return false;
			}
		} else {
			return false;
		}
		
		partition.clear();
	}
}

bool Fragments::Lookup(const vector<string>& dimensions, const vector<Condition>& conditions) {
	
}
