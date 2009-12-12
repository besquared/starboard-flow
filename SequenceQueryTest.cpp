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
			this->query = new SequenceQuery("/tmp/flow");
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->query);
			delete(this->subway);
		}
	};
	
	TEST_F(SequenceQueryTest, MaterializesSingleTable) {
//		sequence->clusters->push_back("card-id")
//		sequence->clusters->push_back("day")
//		
//		sequence->groupings->push_back("fare-group")
//		sequence->groupings->push_back("day")
//
//		sequence->conditions->gte("day", "20091209")
//		
//		sequence->template->push_back("X", "x1", "station", {'action' => 'in'})
//		sequence->template->push_back("Y", "y1", "station", {'action' => 'out'})
//		sequence->template->push_back("Y", "y2", "station", {'action' => 'in'})
//		sequence->template->push_back("X", "x2", "station", {'action' => 'out'})
	}
}  // namespace
