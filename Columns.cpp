/*
 *  Columns.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/30/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Columns.h"

Columns::Columns(Table *Table) {
	this->table = table;
	this->columns = new map<string, int>;
}

Columns::~Columns() {
	delete(this->columns);
}

/*
 * Modifying
 */

void Columns::push_back(shared_ptr<Column> column) {
	vector< shared_ptr<Column> >::push_back(column);
}

void Columns::push_back(const string& name, shared_ptr<Column> column) {
	if(!this->exist(name)) {
		this->push_back(column);
		this->columns->insert(pair<string, int>(name, this->size() - 1));
	}
}

void Columns::erase(const string& name) {
	int position = this->position(name);
	
	// We need to reorganize our map if we erase things
	if(position >= 0) {
		this->columns->erase(name);

		map<string, int>::iterator index;
		for(index = this->columns->begin(); index != this->columns->end(); index++) {
			if(index->second > position) {
				(*this->columns)[index->first]--;
			}
		}
		
		vector< shared_ptr<Column> >::erase(this->begin() + position);
	}
}

/*
 * Accessing
 */

shared_ptr<Column> Columns::at(int position) {
	return vector< shared_ptr<Column> >::at(position);
}

shared_ptr<Column> Columns::at(const string& name) {
	int position = this->position(name);
	
	if(position >= 0) {
		return this->at(position);
	} else {
		return shared_ptr<Column>();
	}	
}

shared_ptr<Column> Columns::operator[](int position) {
	return this->at(position);
}

shared_ptr<Column> Columns::operator[](const string& name) {
	return this->at(name);
}

shared_ptr<Column> Columns::operator[](const char* name) {
	return this->at(string(name));
}

/*
 * Additional Indexing
 */
bool Columns::exist(const string& name) {
	int position = this->position(name);
	
	if(position >= 0) {
		return true;
	} else {
		return false;	
	}
}

int Columns::position(const string& name) {
	map<string, int>::iterator found = this->columns->find(name);
	
	if(found != this->columns->end()) {
		return found->second;
	} else {
		return -1;
	}	
}
