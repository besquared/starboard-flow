/*
 *  EventTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Engine/Sequential/Event.h>

using namespace Flow::Engine;

namespace {
	class SequentialEventTest : public ::testing::Test {
	protected:
		SequentialEventTest() {}
		virtual ~SequentialEventTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(SequentialEventTest, Compares) {
		Sequential::Event wheaton(1, "x1", "wheaton");
		Sequential::Event pentagon(2, "x1", "pentagon");
		
		ASSERT_EQ(true, wheaton < pentagon);
	}
}  // namespace
