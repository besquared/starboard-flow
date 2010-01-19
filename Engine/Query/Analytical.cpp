/*
 *  Analytical.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Analytical.h"

Query::Analytical::Analytical() : Query::Base::Base() {}

void Query::Analytical::Measures(set<string>& results) {
	aggregates->measure_names(results);
}

// Get a set of dims we're instantiating and their values
void Query::Analytical::Instantiate(map<string, string>& results) {
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value != "?") results[condition->column] = equals->value;			
		}
	}
}

void Query::Analytical::InstantiatedValues(vector<string>& results) {
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value != "?") results.push_back(equals->value);
		}
	}
}

// Get a set of dims we're inquiring and their conditions
void Query::Analytical::Inquire(set<string>& dimensions, Conditions& conditions) {
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value == "?") {
				conditions.push_back(condition);
				dimensions.insert(condition->column);
			}
		} else {
			conditions.push_back(condition);
			dimensions.insert(condition->column);
		}
	}
}

// Get a list of the dims we're instantiating and inquiring
void Query::Analytical::Dimensions(vector<string>& instantiated, vector<string>& inquired) {
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
			static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value == "?") {
				inquired.push_back(condition->column);
			} else {
				instantiated.push_back(condition->column);
			}
		} else {
			inquired.push_back(condition->column);
		}
	}	
}
