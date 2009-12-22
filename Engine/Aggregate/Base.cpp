/*
 *  Base.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Base.h"

Engine::Aggregate::Base::Base(const string& measure) {
	this->measures.push_back(measure);
}

Engine::Aggregate::Base::Base(const vector<string>& measures) {
	this->measures = measures;
}