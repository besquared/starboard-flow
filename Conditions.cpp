/*
 *  Conditions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Conditions.h"

void Conditions::Eq(const string& name, const string& value) {
	shared_ptr<Condition::Base> eq(new Condition::Eq(name, value));
	vector< shared_ptr<Condition::Base> >::push_back(eq);
}

void Conditions::Gt(const string& name, const string& value) {
	shared_ptr<Condition::Base> gt(new Condition::Gt(name, value));
	vector< shared_ptr<Condition::Base> >::push_back(gt);
}

void Conditions::Gte(const string& name, const string& value) {
	shared_ptr<Condition::Base> gte(new Condition::Gte(name, value));
	vector< shared_ptr<Condition::Base> >::push_back(gte);
}

void Conditions::Lt(const string& name, const string& value) {
	shared_ptr<Condition::Base> lt(new Condition::Lt(name, value));
	vector< shared_ptr<Condition::Base> >::push_back(lt);
}

void Conditions::Lte(const string& name, const string& value) {
	shared_ptr<Condition::Base> lte(new Condition::Lte(name, value));
	vector< shared_ptr<Condition::Base> >::push_back(lte);
}

void Conditions::In(const string& name, const vector<string>& values) {
	shared_ptr<Condition::Base> in(new Condition::In(name, values));
	vector< shared_ptr<Condition::Base> >::push_back(in);
}

/*
 * Application
 */

void Conditions::Apply(const string& column, vector<string>& values) const {
	shared_ptr<Condition::Base> condition;
	for(size_t i = 0; i < this->size(); i++) {
		condition = this->at(i);
		if(condition != NULL && condition->column == column) {
			condition->Apply(values);
		}
	}
}