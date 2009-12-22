/*
 *  ColumnsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/8/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include "TestHelper.h"

namespace {
	class ColumnsTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		ColumnsTest() {}
		virtual ~ColumnsTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(ColumnsTest, InsertsColumns) {
		// PENDING
	}
	
	TEST_F(ColumnsTest, FindsColumn) {
		// PENDING
	}
	
	TEST_F(ColumnsTest, ErasesColumns) {
		// PENDING
	}
}  // namespace
