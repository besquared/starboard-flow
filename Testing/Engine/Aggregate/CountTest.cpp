/*
 *  CountTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>

using namespace ::Engine;

namespace {
	class CountTest : public ::testing::Test {
	protected:
		CountTest() {}
		virtual ~CountTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(CountTest, HasAlias) {
		Aggregate::Count count("sales");
		EXPECT_EQ("count_sales", count.alias());
		
		Aggregate::Count count_alias("sales", "number_of_sales");
		EXPECT_EQ("number_of_sales", count_alias.alias());
	}
	
	TEST_F(CountTest, CountsGroup) {
		vector<string> values;
		values.push_back("S1");
		values.push_back("Fall");
		
		Group s1_fall(values);
		
		s1_fall.push_back(1);
		s1_fall.push_back(2);
		s1_fall.push_measure("sales", 3);
		s1_fall.push_measure("sales", 6);
		
		Aggregate::Count("sales").apply(s1_fall);
		EXPECT_EQ(2, s1_fall.aggregate("count_sales"));
	}
	
	TEST_F(CountTest, CountsGroups) {
		vector<string> dims;
		dims.push_back("store");
		dims.push_back("season");
		Groups base_table(dims);
		
		vector<string> s1_fall_values;
		s1_fall_values.push_back("S1");
		s1_fall_values.push_back("Fall");
		Group s1_fall(s1_fall_values);
		
		s1_fall.push_back(1);
		s1_fall.push_back(2);
		s1_fall.push_measure("sales", 3);
		s1_fall.push_measure("sales", 6);
		
		vector<string> s2_fall_values;
		s2_fall_values.push_back("S2");
		s2_fall_values.push_back("Fall");
		Group s2_fall(s2_fall_values);
		
		s2_fall.push_back(3);
		s2_fall.push_back(4);
		s2_fall.push_measure("sales", 3);
		s2_fall.push_measure("sales", 3);
		
		base_table.push_back(s1_fall);
		base_table.push_back(s2_fall);
		
		Aggregate::Count("sales").apply(base_table);
		ASSERT_EQ(2, base_table.size());
		EXPECT_EQ(2, base_table[0].aggregate("count_sales"));	
		EXPECT_EQ(2, base_table[1].aggregate("count_sales"));
	}
}
