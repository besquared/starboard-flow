/*
 *  PatternTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include <Engine/Sequential/Pattern.h>

using namespace Flow::Engine;

namespace {
	class PatternTest : public ::testing::Test {
	protected:
		PatternTest() {}
		virtual ~PatternTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(PatternTest, Instantiates) {
		Sequential::Pattern pattern;
		pattern.push_back("station", "X", "x1");
		
		ASSERT_EQ(1, pattern.size());
		EXPECT_EQ("station", pattern[0]->name);
		EXPECT_EQ("X", pattern[0]->symbol);
		EXPECT_EQ("x1", pattern[0]->alias);
	}	
}  // namespace
