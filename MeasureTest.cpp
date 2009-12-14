/*
 *  MeasureTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class MeasureTest : public ::testing::Test {
	protected:
		Measure* database;
		
		MeasureTest() {}
		virtual ~MeasureTest() {}
		
		virtual void SetUp() {
			this->database = new Measure("/tmp/flow", "test");
			
			this->database->Create();
			this->database->Truncate();
			
			tuple<bool, string> open = this->database->OpenWriter();
			
			if(!open.get<0>()) {
				FAIL() << "Could not open measure database => " << open.get<1>() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(MeasureTest, PutsAndGetsValues) {
		tuple<bool, string> put = this->database->Put(100, 100.25);
		
		if(!put.get<0>()) {
			FAIL() << "Could not store measure value => " << put.get<1>();
		}
		
		ASSERT_EQ(100.25, this->database->Get(100));
	}
	
	TEST_F(MeasureTest, PutsAndGetsMultipleValues) {
		for(double i = 1; i <= 2; i++) {
			this->database->Put(i, i);
		}
		
		vector<RecordID> keys;
		for(RecordID k = 1; k <= 2; k++) {
			keys.push_back(k);
		}
		
		vector<double> values;
		this->database->Get(keys, values);
		
		ASSERT_EQ(2, values.size());
		EXPECT_EQ(1, values[0]);
		EXPECT_EQ(2, values[1]);
	}
	
	TEST_F(MeasureTest, PerformsTransactions) {
	}
}