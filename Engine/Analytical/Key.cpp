/*
 *  Key.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/2/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Key.h"

using namespace Flow::Engine;

Analytical::Key::Key(const vector<string>& components) {
	this->components = components;
	this->key = boost::hash_range(components.begin(), components.end());
}

bool Analytical::Key::operator<(Analytical::Key& other) {
	return this->key < other.key;
}

bool Analytical::Key::operator==(Analytical::Key& other) {
	return this->key == other.key;
}