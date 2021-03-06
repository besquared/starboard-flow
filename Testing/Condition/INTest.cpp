/*
 *  INTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

using namespace Condition;

namespace {
	class INTest : public ::testing::Test {
	protected:
		
		INTest() {}
		virtual ~INTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(INTest, Applies) {
		vector<string> include;
		include.push_back("2009");
		include.push_back("2010");
		
		In in("year", include);
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		in.Apply(values);
		
		ASSERT_EQ(2, values.size());
		ASSERT_EQ("2009", values[0]);
		ASSERT_EQ("2010", values[1]);
	}
	
	TEST_F(INTest, AppliesNegation) {
		// PENDING
	}
}  // namespace
