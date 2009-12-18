/*
 *  RecordListTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class RecordListTest : public ::testing::Test {
	protected:
		RecordListTest() {}
		virtual ~RecordListTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(RecordListTest, Intersects) {}
	TEST_F(RecordListTest, Merges) {}
}