/*
 *  Index.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Index.h"

Domain::Data::Index::Index(const string& path) : Domain::Data::BDB::BDB(path, "fragments") {}

bool Domain::Data::Index::Create(const string& path) {
	return Domain::Data::BDB::Create(path, "fragments");
}

/*
 * Looks up a list of record ids from a single index key
 */
bool Domain::Data::Index::Lookup(const ValueMap& dimensions, RIDList& results) {
	vector<string> elements;
	map<string, string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		elements.push_back(this->Component(dimension->first, dimension->second));
	}
	
	return Domain::Data::BDB::Get(this->Key(elements), results);
}

/*
 * Looks up unique values for a given set of dimensions
 */
bool Domain::Data::Index::Lookup(const set<string>& dimensions, ValuesMap& results) {
	vector<string> component;
	set<string>::const_iterator dimension;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		Domain::Data::BDB::Get(this->ValuesKey(*dimension), results[*dimension]);
	}
	
	return true;
}

/*
 * Looks up the records for a list of dimension values
 */
bool Domain::Data::Index::Lookup(const string& dimension, const vector<string>& values, RIDMap& results) {
	for(size_t i = 0; i < values.size(); i++) {
		Domain::Data::BDB::Get(this->Key(this->Component(dimension, values[i])), results[values[i]]);
	}
	
	return true;
}

/*
 * Insert a dimensional row
 */
bool Domain::Data::Index::Insert(const Record& record) {
	vector<string> elements;
	Record::const_iterator element;
	for(element = record.begin(); element != record.end(); element++) {
		elements.push_back(this->Component(element->first, element->second));
	}
	
	vector< vector<string> > sets = this->PowerSet(elements);
	
	for(size_t i = 0; i < sets.size(); i++) {
		Domain::Data::BDB::PutCat(this->Key(sets[i]), record.id);
	}
						 
	this->InsertValues(record);
	
	return true;
}

/*
 * Insert dimension values
 */
bool Domain::Data::Index::InsertValues(const Record& record) {
	int count;
	map<string, string>::const_iterator dimension;
	for(dimension = record.begin(); dimension != record.end(); dimension++) {
		if(Domain::Data::BDB::Add(this->ValueKey(dimension->first, dimension->second), 1, count)) {
			if(count == 1) {
				Domain::Data::BDB::PutDup(this->ValuesKey(dimension->first), dimension->second);
			}
		}
	}
	
	return true;
}

/*
 * Key Management
 */
string Domain::Data::Index::Key(const string& component) {
	return "<" + component + ">";
}

string Domain::Data::Index::Key(const vector<string>& components) {
	return this->Key(boost::join(components, ":"));
}

string Domain::Data::Index::ValuesKey(const string& dimension) {
	return "[" + dimension + "]:values";
}

string Domain::Data::Index::ValueKey(const string& dimension, const string& value) {
	return "[" + dimension + "]:[" + value + "]";
}

string Domain::Data::Index::Component(const string& dimension, const string& value) {
	return "[" + dimension + ":" + value + "]";
}

vector< vector<string> > Domain::Data::Index::PowerSet(vector<string>& values) {
	vector< vector<string> > results;
	results.push_back(vector<string>());
	
	for(unsigned int i = 1; i <= (1 << values.size()) - 1; i++) {
		vector<string> combination;
		for(int j = 0; j <= values.size() - 1; j++) {
			if(this->IsSet(&i, j)) { combination.push_back(values[j]); }
		}
		
		if(combination.size() > 0) { results.push_back(combination); }
	}
	
	return results;
}

bool Domain::Data::Index::IsSet(const unsigned int *set, int i) {
	return (set[i / 32] & (1 << (i & 31)));
}
