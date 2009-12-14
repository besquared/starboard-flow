/*
 *  Master.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/13/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Master.h"

Master::Master(const string& path) : BDB::BDB(path, "master") {}

/*
 * Returns a list of all fragments
 */
bool Master::Fragments(vector<string>& results) {
	return BDB::Get("fragments", results);
}

/*
 * Returns the fragment which contains the given dimension
 */
bool Master::Fragment(const string& dimension, string& result) {
	return BDB::Get(dimension, result);
}

/*
 * Returns a list of all dimensions in the database
 */
bool Master::Dimensions(set<string>& results) {
	return BDB::Get("dimensions", results);
}

/*
 * Returns a list of all dimensions in the given fragment
 */
bool Master::Dimensions(const string& fragment, set<string>& results) {
	return BDB::Get(fragment, results);
}

/*
 * Returns a list of all dimensions *not* in the database
 */
bool Master::Dimensions(const set<string>& dimensions, set<string>& results) {
	set<string> existing;
	
	if(this->Dimensions(existing)) {
		set_difference(dimensions.begin(), dimensions.end(), 
									 existing.begin(), existing.end(),
									 insert_iterator< set<string> >(results, results.end()));
		
		return true;
	} else {
		return false;
	}
}

/*
 * Generates all the necessary fragments to hold dimensions
 */
bool Master::Allocate(const set<string>& dimensions) {
	set<string> alldims;
	set<string> newdims;
	this->Dimensions(alldims);
	this->Dimensions(dimensions, newdims);
	
	set<string>::iterator dimension;
	int current_fragment = alldims.size() / FRAGMENT_SIZE;
	for(dimension = newdims.begin(); dimension != newdims.end(); dimension++) {
		string fragment; 
		if(alldims.size() % FRAGMENT_SIZE == 0) {
			current_fragment++;
			fragment = lexical_cast<string>(current_fragment);
			
			BDB::PutDup("fragments", fragment);
			BDB::Create(this->path, "fragment" + fragment);
		} else {
			fragment = lexical_cast<string>(current_fragment);
		}
		
		BDB::Put(*dimension, fragment);
		BDB::PutDup(fragment, *dimension);
		BDB::PutDup("dimensions", *dimension);

		alldims.insert(*dimension);
	}
		
	return true;
}

/*
 * Generates a new global record id
 */
bool Master::GenerateRecordID(RecordID& result) {
	return BDB::Add("records", 1, result);
}