/*
 *  UtilityTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/27/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class UtilityTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		UtilityTest() {}
		virtual ~UtilityTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	
	TEST_F(UtilityTest, ComputesPowerset) {
		vector<string> values;
		values.push_back("a1");
		values.push_back("b1");
		values.push_back("c3");
		
		// 10,000 runs in 530 ms
		vector< vector<string> > powerset;
		powerset = Common::PowerSet(values);
		
		ASSERT_EQ(8, powerset.size());
	}
	
	TEST_F(UtilityTest, ComputesRecordIDIntersection) {
		vector<RecordID> values;
		values.push_back(1);
		values.push_back(2);
		values.push_back(3);
		
		vector<RecordID> values2;
		values2.push_back(2);
		values2.push_back(3);
		values2.push_back(4);
		
		vector<RecordID> intersection = Common::Intersect(values, values2);
		
		ASSERT_EQ(2, intersection.size());
		EXPECT_EQ(2, intersection[0]);
		EXPECT_EQ(3, intersection[1]);
	}
	
	TEST_F(UtilityTest, ComputesStringIntersection) {
		vector<string> values;
		values.push_back("1");
		values.push_back("2");
		values.push_back("3");
		
		vector<string> values2;
		values2.push_back("2");
		values2.push_back("3");
		values2.push_back("4");
		
		vector<string> intersection = Common::Intersect(values, values2);
		
		ASSERT_EQ(2, intersection.size());
		EXPECT_EQ("2", intersection[0]);
		EXPECT_EQ("3", intersection[1]);		
	}
}  // namespace


