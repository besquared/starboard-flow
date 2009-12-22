/*
 *  Dimensions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimensions.h"

Domain::Dimensions::Dimensions(const string& path) {
	this->path = path;
}

bool Domain::Dimensions::Insert(const Data::Record& record) {
	map<string, string>::const_iterator dimension;
	for(dimension = record.begin(); dimension != record.end(); dimension++) {
		Data::Dimension database(this->path, dimension->first);

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

void Domain::Dimensions::Lookup(const string& dimension, const Data::RIDList& records, vector<string>& results) {
	Data::RIDList::const_iterator record;
	Data::Dimension database(this->path, dimension);
	if(database.OpenReader()) { 
		database.Lookup(records, results);
		database.Close();
	}
}
