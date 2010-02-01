/*
 *  Dimension.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Engine/Sequential/Dimension.h>

Engine::Sequential::Dimension::Dimension(const string& name, const string& symbol, const string& alias) {
	this->name = name;
	this->symbol = symbol;
	this->alias = alias;
}

Engine::Sequential::Dimension::Dimension(const string& name, const string& symbol, const string& alias, const Conditions& conditions) {
	this->name = name;
	this->symbol = symbol;
	this->alias = alias;
	this->conditions = conditions;
}

bool Engine::Sequential::Dimension::match(Group& haystack, size_t position) {
  cout << "Checking position " << position << endl;
  return true;
}