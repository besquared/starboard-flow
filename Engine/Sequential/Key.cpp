/*
 *  Key.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Engine/Sequential/Key.h>

using namespace Flow::Engine;

Sequential::Key::Key(const vector<string>& components) {
	this->components = components;
	this->key = boost::hash_range(components.begin(), components.end());
}

bool Sequential::Key::operator<(Sequential::Key& other) {
	return this->key < other.key;
}

bool Sequential::Key::operator==(Sequential::Key& other) {
	return this->key == other.key;
}