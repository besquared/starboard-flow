/*
 *  KeyTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include <Engine/Sequential/Key.h>

using namespace Flow::Engine;

namespace {
	class KeyTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		KeyTest() {}
		virtual ~KeyTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(KeyTest, Compares) {
		vector<string> components;
		components.push_back("user");
		components.push_back("20091020");
		
		Sequential::Key first(components);
		Sequential::Key second(components);
		
		ASSERT_EQ(true, first == second);
		
		components.push_back("red");
		
		Sequential::Key third(components);
		
		ASSERT_EQ(false, first == third);
		ASSERT_EQ(false, second == third);
	}
	
	TEST_F(KeyTest, Benchmarks) {
//		vector<string> components;
//		components.push_back("user");
//		components.push_back("20091020");
//		
//		for(int i = 0; i < 100000; i++) {
//			Key key(components);
//		}
	}
}  // namespace
