/*
 *  GTTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class GTTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		GTTest() {}
		virtual ~GTTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(GTTest, Applies) {		
		GT gt("year", "2008");
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		gt.Apply(values);
		
		ASSERT_EQ(2, values.size());
		ASSERT_EQ("2009", values[0]);
		ASSERT_EQ("2010", values[1]);
	}
}  // namespace
