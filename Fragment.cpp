/*
 *  Fragment.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Fragment.h"

Fragment::Fragment(const string& path, const string& name) : BDB::BDB(path, name) {}

bool Fragment::Lookup(const map<string, string>& values, vector<RecordID>& results) {
	return true;
}

bool Fragment::Lookup(const set<string>& dimensions, map< string, vector<string> >& results) {
	return true;
}

bool Fragment::Lookup(const string& dimension, const vector<string>& values, map<string, RecordID>& results) {
	return true;
}

bool Fragment::Insert(const RecordID record, const map<string, string>& dimensions) {
	vector<string> elements;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		elements.push_back("[" + dimension->first + ":" + dimension->second + "]");
	}
	
	vector< vector<string> > sets = Common::PowerSet(elements);
	
	for(size_t i = 0; i < sets.size(); i++) {
		BDB::PutDup("<" + boost::join(sets[i], ":") + ">", record);
	}
	
	return true;
}

