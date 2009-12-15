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
	
	TEST_F(BDBTest, PutsAndGetsStrings) {
		string key = "key";
		string value = "value";
		
		string retrieved;
		ASSERT_EQ(true, this->database->Put(key, value));
		ASSERT_EQ(true, this->database->Get(key, retrieved));
		ASSERT_EQ(value, retrieved);
	}
	
	TEST_F(BDBTest, PutsAndGetsDuplicateStrings) {
		string key = "key";
		vector<string> retrieved;

		ASSERT_EQ(true, this->database->PutDup(key, "value1"));
		ASSERT_EQ(true, this->database->PutDup(key, "value2"));
		ASSERT_EQ(true, this->database->Get(key, retrieved));
		
		ASSERT_EQ(2, retrieved.size());
		ASSERT_EQ("value1", retrieved[0]);
		ASSERT_EQ("value2", retrieved[1]);
	}
	
	TEST_F(BDBTest, PutsAndGetsDuplicateSetStrings) {
		string key = "key";
		set<string> retrieved;

		ASSERT_EQ(true, this->database->PutDup(key, "value1"));
		ASSERT_EQ(true, this->database->PutDup(key, "value2"));
		ASSERT_EQ(true, this->database->PutDup(key, "value2"));
		ASSERT_EQ(true, this->database->Get(key, retrieved));
		
		ASSERT_EQ(2, retrieved.size());
		ASSERT_EQ(1, retrieved.count("value1"));
		ASSERT_EQ(1, retrieved.count("value2"));
	}
	
	
	TEST_F(BDBTest, PutsAndGetsDuplicateRecords) {
		string key = "key";
		vector<RecordID> values;
		values.push_back(1.0);
		values.push_back(2.0);
		
		vector<RecordID> retrieved;
		ASSERT_EQ(true, this->database->PutDup(key, values[0]));
		ASSERT_EQ(true, this->database->PutDup(key, values[1]));
		ASSERT_EQ(true, this->database->Get(key, retrieved));
		
		ASSERT_EQ(2, retrieved.size());
		ASSERT_EQ(1.0, retrieved[0]);
		ASSERT_EQ(2.0, retrieved[1]);		
	}
	
	TEST_F(BDBTest, AddsIntsAndDoubles) {
		string key;
		
		int eger;
		key = "intkey";
		ASSERT_EQ(true, this->database->Add(key, 5, eger));
		EXPECT_EQ(5, eger);
		
		double dees;
		key = "doublekey";
		ASSERT_EQ(true, this->database->Add(key, 3.55, dees));
		EXPECT_EQ(3.55, dees);
	}
}