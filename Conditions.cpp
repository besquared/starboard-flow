/*
 *  Conditions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Conditions.h"

void Conditions::eq(const string& name, const string& value) {
	vector< shared_ptr<Condition> >::push_back(shared_ptr<Condition>(new EQ(name, value)));
}

void Conditions::gt(const string& name, const string& value) {
	vector< shared_ptr<Condition> >::push_back(shared_ptr<Condition>(new GT(name, value)));
}

void Conditions::gte(const string& name, const string& value) {
	vector< shared_ptr<Condition> >::push_back(shared_ptr<Condition>(new GTE(name, value)));
}

void Conditions::lt(const string& name, const string& value) {
	vector< shared_ptr<Condition> >::push_back(shared_ptr<Condition>(new LT(name, value)));
}

void Conditions::lte(const string& name, const string& value) {
	vector< shared_ptr<Condition> >::push_back(shared_ptr<Condition>(new LTE(name, value)));
}

void Conditions::in(const string& name, const vector<string>& values) {
	vector< shared_ptr<Condition> >::push_back(shared_ptr<Condition>(new IN(name, values)));
}

/*
 * Application
 */

void Conditions::Apply(const string& column, vector<string>& values) {
	shared_ptr<Condition> condition;
	for(size_t i = 0; i < this->size(); i++) {
		condition = this->at(i);
		if(condition != NULL && condition->column == column) {
			condition->Apply(values);
		}
	}
}