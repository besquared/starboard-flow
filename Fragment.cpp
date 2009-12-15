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

bool Lookup(const map<string, string>& values, vector<RecordID>& results) {
	return true;
}

bool Lookup(const set<string>& dimensions, map< string, vector<string> >& results) {
	return true;
}

bool Lookup(const string& dimension, const vector<string>& values, map<string, RecordID>& results) {
	return true;
}

bool Insert(RecordID record, const map<string, string>& dimensions) {
	// How do we do this, do we trust that the dimensions work, 
	//  or do we know our own dimensions and only pull out the right ones?
	return true;
}