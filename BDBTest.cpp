/*
 *  BDBTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class BDBTest : public ::testing::Test {
	protected:
		BDB* database;
		
		BDBTest() {}
		virtual ~BDBTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			string name = "bdb-test01";
			
			BDB::Create(path, name);
			database = new BDB(path, name);
			
			this->database->Truncate();
			
			if(!this->database->OpenWriter()) {
				FAIL() << "Could not open database for BDBTest => " << this->database->Error() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(BDBTest, PutsAndGetsValues) {
		string key = "key";
		string value = "value";
		RecordID record = 1;
		
		ASSERT_EQ(true, this->database->Put(key, value));
		ASSERT_EQ(true, this->database->Put(key, record));
	}
}