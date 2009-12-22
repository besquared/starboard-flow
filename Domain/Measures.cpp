/*
 *  Measures.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measures.h"

Measures::Measures(const string& path) {
	this->path = path;
}

bool Measures::Insert(RecordID record, const map<string, double>& measures) {
	map<string, double>::const_iterator measure;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		Measure database(this->path, measure->first);

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

void Measures::Lookup(const string& measure, const RIDList& records, vector<double>& results) {
	RIDList::const_iterator record;
	Measure database(this->path, measure);
	if(database.OpenReader()) { 
		database.Lookup(records, results);
		database.Close();
	}
}
