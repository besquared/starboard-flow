/*
 *  TColumnTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/7/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class TColumnTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		TColumnTest() {}
		virtual ~TColumnTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(TColumnTest, Inspects) {
		TColumn<double> column;
		column.push_back(1.0);
		column.push_back(2.0);
		string inspected = column.Inspect();
		EXPECT_EQ(inspected, "[1, 2]");
	}
}
