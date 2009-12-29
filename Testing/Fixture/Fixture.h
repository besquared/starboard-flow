/*
 *  Fixture.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_fixture_h_
#define _flow_testing_fixture_h_

#include <Testing/TestHelper.h>

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