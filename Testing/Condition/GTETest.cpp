/*
 *  GTETest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

using namespace Condition;

namespace {
	class GTETest : public ::testing::Test {
	protected:		
		GTETest() {}
		virtual ~GTETest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(GTETest, Applies) {		
		Gte gte("year", "2008");
		
		vector<string> values;
		values.push_back("2007");
		values.push_back("2008");
		values.push_back("2009");
		values.push_back("2010");
		
		gte.Apply(values);
		
		ASSERT_EQ(3, values.size());
		ASSERT_EQ("2008", values[0]);
		ASSERT_EQ("2009", values[1]);
		ASSERT_EQ("2010", values[2]);
	}
}  // namespace
