/*
 *  Dimensions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimensions.h"

Dimensions::Dimensions(const string& path) {
	this->path = path;
}

bool Dimensions::Insert(const Record& record) {
	map<string, string>::const_iterator dimension;
	for(dimension = record.begin(); dimension != record.end(); dimension++) {
		Dimension database(this->path, dimension->first);

		if(!database.OpenWriter()) {
			return false;
		}
		
		if(!database.Insert(record.id, dimension->second)) {
			database.Close();
			return false;
		}
		
		database.Close();
	}
	
	return true;
}

bool Dimensions::Lookup(const string& dimension, const RIDList& keys, vector<string>& results) {
	return true;
}
