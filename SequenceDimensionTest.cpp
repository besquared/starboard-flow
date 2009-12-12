/*
 *  SequenceDimensionTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class SequenceDimensionTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		SequenceDimensionTest() {}
		virtual ~SequenceDimensionTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(SequenceDimensionTest, Instantiates) {
		SequenceDimension dimension("station", "X", "x1");
		
		EXPECT_EQ("station", dimension.name);
		EXPECT_EQ("X", dimension.symbol);
		EXPECT_EQ("x1", dimension.alias);
	}	
}  // namespace
