/*
 *  LTETest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include "TestHelper.h"

namespace {
	class LTETest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		LTETest() {}
		virtual ~LTETest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(LTETest, Applies) {		
		LTE lte("year", "2008");
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		lte.Apply(values);
		
		ASSERT_EQ(2, values.size());
		ASSERT_EQ("2007", values[0]);
		ASSERT_EQ("2008", values[1]);
	}
}  // namespace
