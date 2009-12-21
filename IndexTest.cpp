/*
 *  IndexTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class IndexTest : public ::testing::Test {
	protected:
		Index* database;
		
		IndexTest() {}
		virtual ~IndexTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";			
			Index::Create(path);
			database = new Index(path);
			
			this->database->Truncate();
			
			if(!this->database->OpenWriter()) {
				FAIL() << "Could not open database for IndexTest => " << this->database->Error() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(IndexTest, GeneratesKey) {
		vector<string> components;
		components.push_back("first");
		components.push_back("second");
		
		ASSERT_EQ("<first:second>", this->database->Key(components));
	}
	
	TEST_F(IndexTest, GeneratesValuesKey) {
		ASSERT_EQ("[dimension]:values", this->database->ValuesKey("dimension"));
	}
	
	TEST_F(IndexTest, GeneratesValueKey) {
		ASSERT_EQ("[dimension]:[1]", this->database->ValueKey("dimension", "1"));
	}
	
	TEST_F(IndexTest, InsertsValues) {
		Record record(1);
		
		record["day"] = "20091020";
		record["fare-group"] = "Regular";
		record["station"] = "16th";
		ASSERT_EQ(true, this->database->InsertValues(record));
		
		record["fare-group"] = "Senior";
		record["station"] = "24th";
		ASSERT_EQ(true, this->database->InsertValues(record));
		
		vector<string> values;
		
		EXPECT_EQ(true, this->database->Get(this->database->ValuesKey("day"), values));
		ASSERT_EQ(1, values.size());
		EXPECT_EQ("20091020", values[0]);
		
		values.clear();
		
		EXPECT_EQ(true, this->database->Get(this->database->ValuesKey("fare-group"), values));
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("Regular", values[0]);
		EXPECT_EQ("Senior", values[1]);
		
		values.clear();
		
		EXPECT_EQ(true, this->database->Get(this->database->ValuesKey("station"), values));
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("16th", values[0]);
		EXPECT_EQ("24th", values[1]);		
	}
	
	TEST_F(IndexTest, InsertsRecords) {
		Record record(1);
		record["day"] = "20091020";
		record["fare-group"] = "Regular";
		record["station"] = "16th";
		
		ASSERT_EQ(true, this->database->Insert(record));
		
		RIDList records;
		
		ASSERT_EQ(true, this->database->Get("<>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[fare-group:Regular]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[station:16th]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]:[fare-group:Regular]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]:[station:16th]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);
		
		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[fare-group:Regular]:[station:16th]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);

		records.clear();
		
		ASSERT_EQ(true, this->database->Get("<[day:20091020]:[fare-group:Regular]:[station:16th]>", records));
		ASSERT_EQ(1, records.size());
		EXPECT_EQ(1, records[0]);		
	}
	
	TEST_F(IndexTest, InstantiatesRecords) {
		Record record;
		record["day"] = "20091020";
		record["fare-group"] = "Regular";
		record["station"] = "16th";
		
		record.id = 1;
		ASSERT_EQ(true, this->database->Insert(record));
		
		record.id = 2;
		ASSERT_EQ(true, this->database->Insert(record));

		RIDList records;
		ASSERT_EQ(true, this->database->Lookup(record, records));
		ASSERT_EQ(2, records.size());
		EXPECT_EQ(1, records[0]);
		EXPECT_EQ(2, records[1]);
	}

	TEST_F(IndexTest, InquiresDimensionValues) {
		Record record;
		
		record.id = 1;
		record["day"] = "20091020";
		record["fare-group"] = "Regular";
		record["station"] = "16th";		
		ASSERT_EQ(true, this->database->Insert(record));
		
		record.id = 2;
		record["fare-group"] = "Senior";
		ASSERT_EQ(true, this->database->Insert(record));
		
		set<string> lookup;
		lookup.insert("day");
		lookup.insert("fare-group");
		map< string, vector<string> > values;
		ASSERT_EQ(true, this->database->Lookup(lookup, values));
		
		map< string, vector<string> >::iterator dimension;
		for(dimension = values.begin(); dimension != values.end(); dimension++) {
			if(dimension->first == "day") {
				ASSERT_EQ(1, dimension->second.size());
				EXPECT_EQ("20091020", dimension->second[0]);
			} else if(dimension->first == "fare-group") {
				ASSERT_EQ(2, dimension->second.size());
				EXPECT_EQ("Regular", dimension->second[0]);
				EXPECT_EQ("Senior", dimension->second[1]);
			} else {
				FAIL() << "Unexpected dimension in lookup data";
			}
		}
	}
	
	TEST_F(IndexTest, InquiresDimensionValueRecords) {
		Record record;
		
		record.id = 1;
		record["day"] = "20091020";
		record["fare-group"] = "Regular";
		record["station"] = "16th";		
		ASSERT_EQ(true, this->database->Insert(record));
		
		record.id = 2;
		record["fare-group"] = "Senior";
		ASSERT_EQ(true, this->database->Insert(record));
		
		vector<string> values;
		values.push_back("Regular");
		values.push_back("Senior");
		
		RIDMap records;
		ASSERT_EQ(true, this->database->Lookup("fare-group", values, records));
		ASSERT_EQ(1, records["Regular"].size());
		EXPECT_EQ(1, records["Regular"][0]);
		ASSERT_EQ(1, records["Senior"].size());
		EXPECT_EQ(2, records["Senior"][0]);
	}
}