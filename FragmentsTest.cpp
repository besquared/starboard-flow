/*
 *  FragmentsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class FragmentsTest : public ::testing::Test {
	protected:
		Master* master;
		Fragments* fragments;
		
		FragmentsTest() {}
		virtual ~FragmentsTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			
			Master::Create(path);
			this->master = new Master(path);
			this->fragments = new Fragments(this->master);
			
			this->master->Truncate();
			
			if(!this->master->OpenWriter()) {
				FAIL() << "Could not open master database for FragmentsTest => " << this->master->Error() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->master);
		}
	};
	
	TEST_F(FragmentsTest, InsertsRecords) {
		RecordID record = 1;
		map<string, string> dimensions;
		dimensions["day"] = "20091020";
		dimensions["fare-group"] = "Regular";
		dimensions["station"] = "16th";
		
		ASSERT_EQ(true, this->fragments->Insert(record, dimensions));
	}	
}