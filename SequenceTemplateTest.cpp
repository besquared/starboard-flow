/*
 *  SequenceTemplateTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class SequenceTemplateTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		SequenceTemplateTest() {}
		virtual ~SequenceTemplateTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(SequenceTemplateTest, Instantiates) {
		SequenceTemplate pattern;
		pattern.push_back("station", "X", "x1");
		
		ASSERT_EQ(1, pattern.size());
		EXPECT_EQ("station", pattern[0]->name);
		EXPECT_EQ("X", pattern[0]->symbol);
		EXPECT_EQ("x1", pattern[0]->alias);
	}	
}  // namespace
