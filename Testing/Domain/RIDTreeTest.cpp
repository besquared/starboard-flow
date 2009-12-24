/*
 *  RIDTreeTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class RIDTreeTest : public ::testing::Test {
	protected:
		RIDTreeTest() {}
		virtual ~RIDTreeTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(RIDTreeTest, Initializes) {
		RIDTree rtree;
		ASSERT_EQ(0, rtree.size());
	}
	
	TEST_F(RIDTreeTest, Intersects) {
	}
	
	TEST_F(RIDTreeTest, Merges) {
	}
}