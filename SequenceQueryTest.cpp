/*
 *  SequenceQueryTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include "SubwayFixture.h"

namespace {
	class SequenceQueryTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		SequenceQuery *query;
		SubwayFixture *subway;
		
		SequenceQueryTest() {}
		virtual ~SequenceQueryTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->subway = new SubwayFixture("/tmp/flow");			
			this->query = new SequenceQuery(".");
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->query);
			delete(this->subway);
		}
	};
	
	TEST_F(SequenceQueryTest, MaterializesSingleTable) {
	}
}  // namespace
