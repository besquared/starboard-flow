/*
 *  Index.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Index.h"

Index::Index(const string& path) : BDB::BDB(path, "fragments") {}

bool Index::Create(const string& path) {
	return BDB::Create(path, "fragments");
}

/*
 * Looks up a list of record ids from a single index key
 */
bool Index::Lookup(const map<string, string>& dimensions, RIDList& results) {
	vector<string> elements;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		elements.push_back(this->Component(dimension->first, dimension->second));
	}
	
	return BDB::Get(this->Key(elements), results);
}

/*
 * Looks up unique values for a given set of dimensions
 */
bool Index::Lookup(const set<string>& dimensions, ValuesMap& results) {
	vector<string> component;
	set<string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		BDB::Get(this->ValuesKey(*dimension), results[*dimension]);
	}
	
	return true;
}

/*
 * Looks up the records for a list of dimension values
 */
bool Index::Lookup(const string& dimension, const vector<string>& values, RIDMap& results) {
	for(size_t i = 0; i < values.size(); i++) {
		BDB::Get(this->Key(this->Component(dimension, values[i])), results[values[i]]);
	}
	
	return true;
}

/*
 * Insert dimension values
 */
bool Index::Insert(const map<string, string>& dimensions) {
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
bool Index::Insert(const RecordID record, const map<string, string>& dimensions) {
	vector<string> elements;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		elements.push_back(this->Component(dimension->first, dimension->second));
	}
	
	vector< vector<string> > sets = Common::PowerSet(elements);
	
	for(size_t i = 0; i < sets.size(); i++) {
		BDB::PutCat(this->Key(sets[i]), record);
	}
						 
	this->Insert(dimensions);
	
	return true;
}

string Index::Key(const string& component) {
	return "<" + component + ">";
}

string Index::Key(const vector<string>& components) {
	return this->Key(boost::join(components, ":"));
}

string Index::ValuesKey(const string& dimension) {
	return "[" + dimension + "]:values";
}

string Index::ValueKey(const string& dimension, const string& value) {
	return "[" + dimension + "]:[" + value + "]";
}

string Index::Component(const string& dimension, const string& value) {
	return "[" + dimension + ":" + value + "]";
}