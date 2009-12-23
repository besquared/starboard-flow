/*
 *  Template.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Template.h"

using namespace Flow::Engine;

Sequential::Template::Template() {
	this->matching = SUBSTRING;
	this->restriction = LEFT_MATCH;
}

void Sequential::Template::push_back(const string& name, const string& symbol, const string& alias) {
	vector< boost::shared_ptr<Sequential::Dimension> >::push_back(
		boost::shared_ptr<Sequential::Dimension>(new Sequential::Dimension(name, symbol, alias))
	);
}

void Sequential::Template::push_back(const string& name, const string& symbol, const string& alias, const Conditions& conditions) {
	vector< boost::shared_ptr<Sequential::Dimension> >::push_back(
		boost::shared_ptr<Sequential::Dimension>(new Sequential::Dimension(name, symbol, alias, conditions))
	);
}
