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

Analytical::Query::Query(Domain::Base* domain) {
	this->domain = domain;
	this->conditions = new Conditions();
	this->aggregates = new Aggregates();
}

bool Analytical::Query::Execute(Groups& results) {
	return Executive(this).Execute(results);
}

// Get a set of dims we're instantiating and their values
void Instantiate(map<string, string>& results) {}

// Get a set of dims we're inquiring and their conditions
void Inquire(set<string>& Dimensions, Conditions& conditions) {}

// Get a list of the dims we're instantiating and inquiring
void Dimensions(vector<string>& instantiated, vector<string>& inquired) {}
