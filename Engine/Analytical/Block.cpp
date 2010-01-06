/*
 *  Block.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 1/2/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Block.h"

void Analytical::Block::push_back(const vector<string>& components, const RIDList& records) {
	this->push_back(pair<Key, RIDList>(Key(components), records));
}