/*
 *  Record.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Record.h"

Domain::Data::Record::Record() {}

Domain::Data::Record::Record(RecordID id) {
	this->id = id;
}

set<string> Domain::Data::Record::Dimensions() const {
	set<string> results;
	
	Domain::Data::Record::const_iterator element;
	for(element = this->begin(); element != this->end(); element++) {
		results.insert(element->first);
	}
	
	return results;
}

vector<string> Domain::Data::Record::Values() const {
	vector<string> results;
	
	Domain::Data::Record::const_iterator element;
	for(element = this->begin(); element != this->end(); element++) {
		results.push_back(element->second);
	}
	
	return results;	
}

Domain::Data::Record Domain::Data::Record::Partition(const set<string>& dimensions) const {
	Record result(this->id);
	
	Domain::Data::Record::const_iterator element;
	for(element = this->begin(); element != this->end(); element++) {
		if(dimensions.find(element->first) != dimensions.end()) {
			result[element->first] = element->second;
		}
	}
	
	return result;
}