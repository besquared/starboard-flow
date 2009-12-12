/*
 *  EQTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/9/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class EqualsTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		EqualsTest() {}
		virtual ~EqualsTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(EqualsTest, Applies) {
		EQ equals("year", "2009");
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		equals.Apply(values);
		
		ASSERT_EQ(1, values.size());
		ASSERT_EQ("2009", values[0]);
	}
	
	TEST_F(EqualsTest, AppliesNegation) {
		EQ equals("year", "2009", true);
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		equals.Apply(values);
		
		ASSERT_EQ(3, values.size());
		ASSERT_EQ("2007", values[0]);
		ASSERT_EQ("2008", values[1]);
		ASSERT_EQ("2010", values[2]);
	}
}  // namespace
