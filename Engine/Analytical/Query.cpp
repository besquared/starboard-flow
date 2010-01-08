/*
 *  Query.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * A query takes a measure and a set of conditions in the form of
 *  {"A" => "a1", "B" => "?", "C" => "*"}
 *
 * and returns a set of column vectors that contains the appropriate answers, 
 * for instance a query like 
 * 
 * {"Product" => "P1", "Store" => "?" : SUM(SALE), COUNT(SALE)} 
 *
 * might return
 *
 * [ [S1, S2, S3], [10.5, 10.8, 10.2], [2, 2, 2] ]
 */

#include "Query.h"

Analytical::Query::Query() {
	this->conditions = new Conditions();
	this->aggregates = new Aggregates();
}

bool Analytical::Query::Execute(Domain::Base* domain, Groups& results) {
	Executive executive(domain, this);
	return this->Execute(executive, results);
}

bool Analytical::Query::Execute(Executive& executive, Groups& results) {
	return executive.Execute(results);
}

void Analytical::Query::Measures(set<string>& results) {
	aggregates->Measures(results);
}

// Get a set of dims we're instantiating and their values
void Analytical::Query::Instantiate(map<string, string>& results) {
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = 
				static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value != "?") results[condition->column] = equals->value;			
		}
	}
}

// Get a set of dims we're inquiring and their conditions
void Analytical::Query::Inquire(set<string>& dimensions, Conditions& conditions) {
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
void Analytical::Query::Dimensions(vector<string>& instantiated, vector<string>& inquired) {
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
