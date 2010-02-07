/*
 *  LTETest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>

using namespace Condition;

namespace {
	class LTETest : public ::testing::Test {
	protected:
		LTETest() {}
		virtual ~LTETest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(LTETest, Applies) {		
		Lte lte("year", "2008");
		
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
