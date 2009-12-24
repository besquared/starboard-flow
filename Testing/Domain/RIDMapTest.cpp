/*
 *  RIDMapTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class RIDMapTest : public ::testing::Test {
	protected:
		RIDMapTest() {}
		virtual ~RIDMapTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(RIDMapTest, Initializes) {
		RIDMap rmap;
		ASSERT_EQ(0, rmap.size());
	}
	
	TEST_F(RIDMapTest, Intersects) {
	}
	
	TEST_F(RIDMapTest, Merges) {
	}
}