/*
 *  DimensionsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class DimensionsTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		Dimensions *dimensions;
		
		DimensionsTest() {}
		virtual ~DimensionsTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->dimensions = new Dimensions("/tmp/flow");			
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->dimensions);
		}		
	};
	
	TEST_F(DimensionsTest, OpensWriter) {
		tuple< bool, string, shared_ptr<Dimension> > opened;
		opened = this->dimensions->OpenWriter("product");
		
		if(!opened.get<0>()) {
			FAIL() << "Could not open measure database sales for writing: " << opened.get<1>() << endl;
		}
	}
	
	TEST_F(DimensionsTest, WritesDimensions) {
		map<string, string> dimensions;
		dimensions["store"] = "S1";
		dimensions["product"] = "P2";
		
		this->dimensions->Insert(1, dimensions);
		this->dimensions->Insert(2, dimensions);
		
		vector<RecordID> records;
		records.push_back(1);
		records.push_back(2);
		
		vector<string> results;
		shared_ptr<Dimension> database;
		tuple< bool, string, shared_ptr<Dimension> > opened;
		
		// Check sales first
		opened = this->dimensions->OpenWriter("store");
		ASSERT_EQ(true, opened.get<0>());
		
		database = opened.get<2>();
		database->Get(records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ("S1", results[0]);
		EXPECT_EQ("S1", results[1]);
		
		results.clear();
		
		// Now tax
		opened = this->dimensions->OpenWriter("product");
		ASSERT_EQ(true, opened.get<0>());
		
		database = opened.get<2>();
		database->Get(records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ("P2", results[0]);
		EXPECT_EQ("P2", results[1]);		
	}
}
