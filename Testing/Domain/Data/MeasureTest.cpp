/*
 *  MeasureTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

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
			
			if(!this->database->OpenWriter()) {
				FAIL() << "Could not open measure database" << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(MeasureTest, PutsAndLooksupValues) {
		if(!this->database->Insert(100, 100.25)) {
			FAIL() << "Could not store measure value";
		}
		
		double value;
		ASSERT_EQ(true, this->database->Lookup(100, value));
		EXPECT_EQ(100.25, value);
	}
	
	TEST_F(MeasureTest, PutsAndLooksupMultipleValues) {
		for(double i = 1; i <= 2; i++) {
			this->database->Insert(i, i);
		}
		
		RIDList keys;
		for(RecordID k = 1; k <= 2; k++) {
			keys.push_back(k);
		}
		
		vector<double> values;
		this->database->Lookup(keys, values);
		
		ASSERT_EQ(2, values.size());
		EXPECT_EQ(1, values[0]);
		EXPECT_EQ(2, values[1]);
	}
}