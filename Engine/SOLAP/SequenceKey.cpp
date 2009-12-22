/*
 *  SequenceKey.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "SequenceKey.h"

SequenceKey::SequenceKey(const vector<string>& components) {
	this->components = components;
	this->key = hash_range(components.begin(), components.end());
}

bool SequenceKey::operator<(SequenceKey& other) {
	return this->key < other.key;
}

bool SequenceKey::operator==(SequenceKey& other) {
	return this->key == other.key;
}