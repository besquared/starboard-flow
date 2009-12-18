/*
 *  FragmentsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include "MockMaster.h"

namespace Mocks = Testing::Database;

namespace {
	class FragmentsTest : public ::testing::Test {
	protected:
		Fragments* fragments;
		
		FragmentsTest() {}
		virtual ~FragmentsTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			Mocks::MockMaster master(path);
			this->fragments = new Fragments(&master);
		}
		
		virtual void TearDown() {
			delete(this->fragments);
		}
	};
	
	TEST_F(FragmentsTest, InsertsRecords) {
		RecordID record = 1;
		map<string, string> dimensions;
		dimensions["day"] = "20091020";
		dimensions["fare-group"] = "Regular";
		dimensions["station"] = "16th";
		
		ASSERT_EQ(true, this->fragments->Insert(record, dimensions));
		// check this stuff
	}
	
//	TEST_F(FragmentsTest, LooksUpRecords) {
//		
//	}
}