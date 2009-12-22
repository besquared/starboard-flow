/*
 *  SubwayFixture.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _subway_fixture_included_
#define _subway_fixture_included_

#include "Fixture.h"
#include "TestHelper.h"

/*
 * +--------+-------+------------+----------+----------+-------------+-----------+--------+
 * | record | name  | fare-group | card-id  | day      | station     | district  | action |
 * +--------|-------|------------|----------|----------|-------------|-----------|--------+
 * | 1      | swipe | regular    | 00000001 | 20091210 | montgomery  | financial | in     |
 * | 2      | swipe | regular    | 00000001 | 20091210 | 16th street | mission   | out    |
 * | 3      | swipe | regular    | 00000001 | 20091210 | 16th street | mission   | in     |
 * | 4      | swipe | regular    | 00000001 | 20091210 | montgomery  | financial | out    |
 * | 5      | swipe | senior     | 00000002 | 20091210 | montgomery  | financial | in     |
 * | 6      | swipe | senior     | 00000002 | 20091210 | 16th street | mission   | out    |
 * +--------+-------+------------+----------+----------+-------------+-----------+--------+
 */

class SubwayFixture : public Fixture {
public:
	
	SubwayFixture(const string& path);
	~SubwayFixture();
	
	vector<string> GetDimensions();
	vector< vector<string> > GetData();
	
	void LoadDimensions();
	void LoadMeasures();
	void LoadFragments();
};

#endif