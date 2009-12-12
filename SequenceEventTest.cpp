/*
 *  SequenceEventTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include "TestHelper.cpp"

namespace {
	class SequenceEventTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		SequenceEventTest() {}
		virtual ~SequenceEventTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(SequenceEventTest, Compares) {
		SequenceEvent wheaton(1, "x1", "wheaton");
		SequenceEvent pentagon(2, "x1", "pentagon");
		
		ASSERT_EQ(true, wheaton < pentagon);
	}
}  // namespace
