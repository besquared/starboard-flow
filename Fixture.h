/*
 *  Fixture.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

class Fixture {
public:
	string path;
	
	Fixture(const string& path);
	
	virtual void Load() = 0;
	virtual void Clean() = 0;
}