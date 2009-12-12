/*
 *  SequenceTemplate.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "SequenceTemplate.h"

SequenceTemplate::SequenceTemplate() {
	this->matching = SUBSTRING;
	this->restriction = LEFT_MATCHED_GO;
}

void SequenceTemplate::push_back(const string& name, const string& symbol, const string& alias) {
	vector< shared_ptr<SequenceDimension> >::push_back(
		shared_ptr<SequenceDimension>(new SequenceDimension(name, symbol, alias))
	);
}

void SequenceTemplate::push_back(const string& name, const string& symbol, const string& alias, const shared_ptr<Conditions> conditions) {
	vector< shared_ptr<SequenceDimension> >::push_back(
		shared_ptr<SequenceDimension>(new SequenceDimension(name, symbol, alias, conditions))
	);
}
