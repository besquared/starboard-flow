/*
 *  Conditions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Conditions.h"

Conditions::Conditions() {
	this->conditions = new map<string, int>;
}

Conditions::~Conditions() {
	delete(this->conditions);
}

/*
 * Modifying
 */

void Conditions::push_back(shared_ptr<Condition> column) {
	vector< shared_ptr<Condition> >::push_back(column);
}

void Conditions::push_back(const string& column, const string& value) {
	shared_ptr<Condition> condition(new EQ(column, value));
	this->push_back(condition);
}

void Conditions::push_back(const string& name, shared_ptr<Condition> column) {
	if(!this->exist(name)) {
		this->push_back(column);
		this->conditions->insert(pair<string, int>(name, this->size() - 1));
	}
}

void Conditions::erase(const string& name) {
	int position = this->position(name);
	
	if(position >= 0) {
		this->conditions->erase(name);
		vector< shared_ptr<Condition> >::erase(this->begin() + position);
	}
}

/*
 * Accessing
 */

shared_ptr<Condition> Conditions::at(int position) {
	return vector< shared_ptr<Condition> >::at(position);
}

shared_ptr<Condition> Conditions::at(const string& name) {
	int position = this->position(name);
	
	if(position >= 0) {
		return this->at(position);
	} else {
		return shared_ptr<Condition>();
	}	
}

shared_ptr<Condition> Conditions::operator[](int position) {
	return this->at(position);
}

shared_ptr<Condition> Conditions::operator[](const string& name) {
	return this->at(name);
}

shared_ptr<Condition> Conditions::operator[](const char* name) {
	return this->at(string(name));
}

/*
 * Additional Indexing
 */
bool Conditions::exist(const string& name) {
	int position = this->position(name);
	
	if(position >= 0) {
		return true;
	} else {
		return false;	
	}
}

int Conditions::position(const string& name) {
	map<string, int>::iterator found = this->conditions->find(name);
	
	if(found != this->conditions->end()) {
		return found->second;
	} else {
		return -1;
	}	
}

/*
 * Application
 */

void Conditions::Apply(const string& column, vector<string>& values) {
	shared_ptr<Condition> condition;
	for(size_t i = 0; i < this->size(); i++) {
		condition = this->at(i);
		if(condition != NULL && condition->column == column) {
			cout << "Applying condition to " << condition->column << endl;
			condition->Apply(values);
		}
	}
}