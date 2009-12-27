/*
 *  DimensionTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include <Engine/Sequential/Dimension.h>

using namespace Flow::Engine;

namespace {
	class SequentialDimensionTest : public ::testing::Test {
	protected:
		SequentialDimensionTest() {}
		virtual ~SequentialDimensionTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(SequentialDimensionTest, Instantiates) {
		Sequential::Dimension dimension("station", "X", "x1");
		
		EXPECT_EQ("station", dimension.name);
		EXPECT_EQ("X", dimension.symbol);
		EXPECT_EQ("x1", dimension.alias);
	}	
}  // namespace
