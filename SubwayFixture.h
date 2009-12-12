/*
 *  SubwayFixture.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Fixture.h"

/*
 * +--------+------------+----------+----------+-------------+-----------+--------+
 * | record | fare-group | card-id  | day      | station     | district  | action |
 * +--------|------------|----------|----------|-------------|-----------|--------+
 * | 1      | regular    | 00000001 | 20091210 | montgomery  | financial | in     |
 * | 2      | regular    | 00000001 | 20091210 | 16th street | mission   | out    |
 * | 3      | regular    | 00000001 | 20091210 | 16th street | mission   | in     |
 * | 4      | regular    | 00000001 | 20091210 | montgomery  | financial | out    |
 * | 5      | regular    | 00000002 | 20091210 | montgomery  | financial | in     |
 * | 6      | regular    | 00000002 | 20091210 | 16th street | mission   | out    |
 * +--------+------------+----------+----------+-------------+-----------+--------+
 */

class Subway : public Fixture {
public:
	
	Subway(const string& path);
	
	void Load();
	void Clean();
	
	void LoadDimensions();
	void LoadMeasures();
	void LoadFragments();
}

Subway::Subway(const string& path) : Fixture::Fixture(path) {}

void Subway::Load() {
	
}

void Subway::Clean() {

}