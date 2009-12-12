/*
 *  SequenceKeyTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class SequenceKeyTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		SequenceKeyTest() {}
		virtual ~SequenceKeyTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(SequenceKeyTest, Compares) {
		vector<string> components;
		components.push_back("user");
		components.push_back("20091020");
		
		SequenceKey first(components);
		SequenceKey second(components);
		
		ASSERT_EQ(true, first == second);
		
		components.push_back("red");
		
		SequenceKey third(components);
		
		ASSERT_EQ(false, first == third);
		ASSERT_EQ(false, second == third);
	}
	
	TEST_F(SequenceKeyTest, Benchmarks) {
//		vector<string> components;
//		components.push_back("user");
//		components.push_back("20091020");
//		
//		for(int i = 0; i < 100000; i++) {
//			SequenceKey key(components);
//		}
	}
}  // namespace
