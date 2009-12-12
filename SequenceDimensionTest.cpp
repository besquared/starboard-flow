/*
 *  SequenceDimensionTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

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
		
		ASSERT_EQ(dimension.name, "station");
		ASSERT_EQ(dimension.symbol, "X");
		ASSERT_EQ(dimension.alias, "x1");
	}	
}  // namespace
