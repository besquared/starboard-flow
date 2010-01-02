/*
 *  Measures.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measures.h"

Domain::Measures::Measures(const string& path) {
	this->path = path;
}

Domain::Measures::~Measures() {}

bool Domain::Measures::Insert(const RecordID record, const map<string, double>& measures) {
	map<string, double>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		Data::Measure database(this->path, measure->first);

		if(!database.OpenWriter()) {
			return false;
		}
		
		if(!database.Insert(record, measure->second)) {
			database.Close();
			return false;
		}
	}
	
	return true;
}

void Domain::Measures::Lookup(const string& measure, const Data::RIDList& records, vector<double>& results) {
	Data::RIDList::const_iterator record;
	Data::Measure database(this->path, measure);
	if(database.OpenReader()) { 
		database.Lookup(records, results);
		database.Close();
	}
}
