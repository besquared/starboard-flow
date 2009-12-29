/*
 *  LTTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>

using namespace Condition;

namespace {
	class LTTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		LTTest() {}
		virtual ~LTTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(LTTest, Applies) {		
		Lt lt("year", "2008");
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		lt.Apply(values);
		
		ASSERT_EQ(1, values.size());
		ASSERT_EQ("2007", values[0]);
	}
}  // namespace
