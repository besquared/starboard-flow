/*
 *  FragmentTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class FragmentTest : public ::testing::Test {
	protected:
		Fragment* database;
		
		FragmentTest() {}
		virtual ~FragmentTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			string fragment = "fragment1";
			
			Fragment::Create(path, fragment);
			database = new Fragment(path, fragment);
			
			this->database->Truncate();
			
			if(!this->database->OpenWriter()) {
				FAIL() << "Could not open database for FragmentTest => " << this->database->Error() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(FragmentTest, GeneratesKey) {
		vector<string> components;
		components.push_back("first");
		components.push_back("second");
		
		ASSERT_EQ("<first:second>", this->database->Key(components));
	}
	
	TEST_F(FragmentTest, GeneratesValuesKey) {
		ASSERT_EQ("[dimension]:values", this->database->ValuesKey("dimension"));
	}
	
	TEST_F(FragmentTest, GeneratesDimensionKey) {
		ASSERT_EQ("[dimension]", this->database->DimensionKey("dimension"));
	}
	
	TEST_F(FragmentTest, InsertsRecords) {
		RecordID record = 1;
		map<string, string> dimensions;
		dimensions["day"] = "20091020";
		dimensions["fare-group"] = "Regular";
		dimensions["station"] = "16th";
		
		ASSERT_EQ(true, this->database->Insert(record, dimensions));
		
		vector<RecordID> records;
		
		ASSERT_EQ(true, this->database->Get("<>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[fare-group:Regular]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[station:16th]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]:[fare-group:Regular]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]:[station:16th]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[fare-group:Regular]:[station:16th]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);

		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]:[fare-group:Regular]:[station:16th]>", records));
		EXPECT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);		
	}
	
	TEST_F(FragmentTest, InstantiatesRecords) {
		RecordID record;

		map<string, string> dimensions;
		dimensions["day"] = "20091020";
		dimensions["fare-group"] = "Regular";
		dimensions["station"] = "16th";
		
		record = 1;
		ASSERT_EQ(true, this->database->Insert(record, dimensions));
		
		record = 2;
		ASSERT_EQ(true, this->database->Insert(record, dimensions));

		vector<RecordID> records;
		
		ASSERT_EQ(true, this->database->Lookup(dimensions, records));
		ASSERT_EQ(2, records.size());
		EXPECT_EQ(1, records[0]);
		EXPECT_EQ(2, records[1]);
	}
}