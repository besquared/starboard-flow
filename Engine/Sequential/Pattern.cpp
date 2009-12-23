/*
 *  Pattern.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Pattern.h"

using namespace Flow::Engine;

Sequential::Pattern::Pattern() {
	this->matching = SUBSTRING;
	this->restriction = LEFT_MATCH;
}

void Sequential::Pattern::push_back(const string& name, const string& symbol, const string& alias) {
	vector< boost::shared_ptr<Sequential::Dimension> >::push_back(
		boost::shared_ptr<Sequential::Dimension>(new Sequential::Dimension(name, symbol, alias))
	);
}

void Sequential::Pattern::push_back(const string& name, const string& symbol, const string& alias, const Conditions& conditions) {
	vector< boost::shared_ptr<Sequential::Dimension> >::push_back(
		boost::shared_ptr<Sequential::Dimension>(new Sequential::Dimension(name, symbol, alias, conditions))
	);
}
