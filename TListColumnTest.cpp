/*
 *  TListColumnTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/7/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class TListColumnTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		TListColumnTest() {}
		virtual ~TListColumnTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(TListColumnTest, Inspects) {
		vector<double> first;
		first.push_back(1);
		first.push_back(2);
		
		vector<double> second;
		second.push_back(3);
		
		TListColumn<double> column;
		column.push_back(first);
		column.push_back(second);
		
		string inspected = column.Inspect();
		EXPECT_EQ(inspected, "[[1, 2], [3]]");
	}
}
