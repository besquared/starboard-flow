/*
 *  MeasuresTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/5/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

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
	
	TEST_F(MeasuresTest, OpensWriter) {
		tuple< bool, string, shared_ptr<Measure> > opened;
		opened = this->measures->OpenWriter("sales");
		
		if(!opened.get<0>()) {
			FAIL() << "Could not open measure database sales for writing: " << opened.get<1>() << endl;
		}
	}
	
	TEST_F(MeasuresTest, WritesMeasures) {
		map<string, double> measures;
		measures["sales"] = 6;
		measures["tax"] = 1;
		
		this->measures->Insert(1, measures);
		this->measures->Insert(2, measures);
		
		vector<RecordID> records;
		records.push_back(1);
		records.push_back(2);
		
		vector<double> results;
		shared_ptr<Measure> database;
		tuple< bool, string, shared_ptr<Measure> > opened;
		
		// Check sales first
		opened = this->measures->OpenWriter("sales");
		ASSERT_EQ(true, opened.get<0>());
		
		database = opened.get<2>();
		database->Get(records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ(6, results[0]);
		EXPECT_EQ(6, results[1]);
		
		results.clear();
		
		// Now tax
		opened = this->measures->OpenWriter("tax");
		ASSERT_EQ(true, opened.get<0>());
		
		database = opened.get<2>();
		database->Get(records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ(1, results[0]);
		EXPECT_EQ(1, results[1]);		
	}
}
