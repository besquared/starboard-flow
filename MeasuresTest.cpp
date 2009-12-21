/*
 *  MeasuresTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/5/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class MeasuresTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		Measures *measures;
		
		MeasuresTest() {}
		virtual ~MeasuresTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->measures = new Measures("/tmp/flow");			
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->measures);
		}		
	};
	
	TEST_F(MeasuresTest, WritesMeasures) {
		map<string, double> measures;
		measures["sales"] = 6;
		measures["tax"] = 1;
		
		this->measures->Insert(1, measures);
		this->measures->Insert(2, measures);
		
		RIDList records;
		records.push_back(1);
		records.push_back(2);
		
		vector<double> results;

		// Check sales first
		this->measures->Lookup("sales", records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ(6, results[0]);
		EXPECT_EQ(6, results[1]);
		
		results.clear();
		
		// Now tax
		this->measures->Lookup("tax", records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ(1, results[0]);
		EXPECT_EQ(1, results[1]);		
	}
}
