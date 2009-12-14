/*
 *  Master.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/13/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Master.h"

Master::Master(const string& path) : BDB::BDB(path) {}

string Master::Path() {
  return this->path + "/" + "master.tcb";
}

/*
 * Returns a list of all fragments
 */
vector<string> Master::Fragments() {
	vector<string> results;
	return results;
}

/*
 * Returns the fragment which contains the given dimension
 */
vector<string> Master::Fragment(const string& dimension) {
	vector<string> results;
	return results;
}

/*
 * Returns a list of all dimensions in the database
 */
vector<string> Master::Dimensions() {
	vector<string> results;
	return results;
}

/*
 * Returns a list of all dimensions in the given fragment
 */
vector<string> Master::Dimensions(const string& fragment) {
	vector<string> results;
	return results;
}

/*
 * Returns a list of all dimensions *not* in the database
 */
vector<string> Master::Dimensions(const set<string>& dimensions) {
	vector<string> results;
	return results;
}

/*
 * Generates all the necessary fragments to hold dimensions
 */
tuple<bool, string> Master::Allocate(const set<string>& dimensions) {
	set<string>::iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		
	}
	
	return make_tuple(ok, success);
}

/*
 * Generates a new global record id
 */
tuple<bool, string, RecordID> Master::GenerateRecordID() {
	string key = "records";
	RecordID newvalue = tcbdbadddouble(this->database, key.c_str(), key.length(), 1);
	
	if(isnan(newvalue)) {
		return make_tuple(error, this->Error(), -1);
	} else {
		return make_tuple(ok, success, newvalue);
	}
}