/*
 *  Fixture.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _fixture_included_
#define _fixture_included_

#include "TestHelper.h"

using namespace std;
using namespace boost;

class Fixture {
public:
	string path;
	
	Fixture(const string& path) {
		this->path = path;
	}
};

#endif