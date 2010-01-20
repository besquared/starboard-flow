/*
 *  DimensionTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>

namespace {
	using namespace Flow::Domain;
	using namespace Flow::Domain::Data;
	
	class DimensionTest : public ::testing::Test {
	protected:
		Dimension* database;
		
		DimensionTest() {}
		virtual ~DimensionTest() {}
		
		virtual void SetUp() {
			this->database = new Dimension("/tmp/flow", "test");
			
			if(!this->database->Create()) {
				FAIL() << "Could not create dimension database" << endl;
			}
			
			if(!this->database->Truncate()) {
				FAIL() << "Could not truncate dimension database" << endl;
			}
			
			if(!this->database->OpenWriter()) {
				FAIL() << "Could not open dimension database" << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(DimensionTest, InsertsAndLooksupValues) {		
		if(!this->database->Insert(100, "S1")) {
			FAIL() << "Could not store dimension value";
		}
		
		string value;
		this->database->Lookup(100, value);
		ASSERT_EQ("S1", value);
	}
	
	TEST_F(DimensionTest, InsertsAndLooksupMultipleValues) {		
		this->database->Insert(1, "S1");
		this->database->Insert(2, "S2");
		
		RIDList keys;
		keys.push_back(1);
		keys.push_back(2);
		
		vector<string> values;
		this->database->Lookup(keys, values);
		
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("S1", values[0]);
		EXPECT_EQ("S2", values[1]);
	}
}