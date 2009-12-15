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

/*
 * Looks up a list of record ids from a single index key
 */
bool Fragment::Lookup(const map<string, string>& dimensions, vector<RecordID>& results) {
	vector<string> elements;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		elements.push_back("[" + dimension->first + ":" + dimension->second + "]");
	}
	
	return BDB::Get(this->Key(elements), results);
}

/*
 * Looks up unique values for a given set of dimensions
 */
bool Fragment::Lookup(const set<string>& dimensions, map< string, vector<string> >& results) {
	set<string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		BDB::Get(this->ValuesKey(*dimension), results[*dimension]);
	}
	
	return true;
}

bool Fragment::Lookup(const string& dimension, const vector<string>& values, map<string, RecordID>& results) {
	return true;
}

/*
 * Insert dimension values
 */
bool Fragment::Insert(const map<string, string>& dimensions) {
	// insert unique values for each dimension
	int count;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		if(BDB::Add(this->ValueKey(dimension->first, dimension->second), 1, count)) {
			if(count == 1) {
				BDB::PutDup(this->ValuesKey(dimension->first), dimension->second);
			}
		}
	}
	
	return true;
}

/*
 * Insert a dimensional row
 */
bool Fragment::Insert(const RecordID record, const map<string, string>& dimensions) {
	vector<string> elements;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		elements.push_back("[" + dimension->first + ":" + dimension->second + "]");
	}
	
	vector< vector<string> > sets = Common::PowerSet(elements);
	
	for(size_t i = 0; i < sets.size(); i++) {
		BDB::PutDup(this->Key(sets[i]), record);
	}
						 
	this->Insert(dimensions);
	
	return true;
}

string Fragment::Key(const vector<string>& components) {
	return "<" + boost::join(components, ":") + ">";
}

string Fragment::ValuesKey(const string& dimension) {
	return "[" + dimension + "]:values";
}

string Fragment::ValueKey(const string& dimension, const string& value) {
	return "[" + dimension + "]:[" + value + "]";
}
