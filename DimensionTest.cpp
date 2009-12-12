/*
 *  DimensionTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include "TestHelper.h"

namespace {
	class DimensionTest : public ::testing::Test {
	protected:
		Dimension* database;
		
		DimensionTest() {}
		virtual ~DimensionTest() {}
		
		virtual void SetUp() {
			this->database = new Dimension("/tmp/flow", "test");
			
			tuple<bool, string> created = this->database->Create();
			
			if(!created.get<0>()) {
				FAIL() << "Could not create dimension database => " << created.get<1>() << endl;
			}
			
			tuple<bool, string> truncated = this->database->Truncate();
			
			if(!truncated.get<0>()) {
				FAIL() << "Could not truncate dimension database => " << truncated.get<1>() << endl;
			}
			
			tuple<bool, string> open = this->database->OpenWriter();
			
			if(!open.get<0>()) {
				FAIL() << "Could not open dimension database => " << open.get<1>() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(DimensionTest, PutsAndGetsValues) {
		tuple<bool, string> put = this->database->Put(100, "S1");
		
		if(!put.get<0>()) {
			FAIL() << "Could not store dimension value => " << put.get<1>();
		}
		
		ASSERT_EQ("S1", this->database->Get(100));
	}
	
	TEST_F(DimensionTest, PutsAndGetsMultipleValues) {		
		this->database->Put(1, "S1");
		this->database->Put(2, "S2");
		
		vector<RecordID> keys;
		keys.push_back(1);
		keys.push_back(2);
		
		vector<string> values;
		this->database->Get(keys, values);
		
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("S1", values[0]);
		EXPECT_EQ("S2", values[1]);
	}
}