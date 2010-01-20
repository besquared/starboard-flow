/*
 *  DimensionsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

namespace {
	using namespace Flow::Domain::Data;
	
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
	
	TEST_F(DimensionsTest, WritesDimensions) {
		Record record;
		record["store"] = "S1";
		record["product"] = "P2";
		
		record.id = 1;
		this->dimensions->Insert(record);
		
		record.id = 2;
		this->dimensions->Insert(record);
		
		RIDList records;
		records.push_back(1);
		records.push_back(2);
		
		vector<string> values;
		
		// Check store first
		this->dimensions->Lookup("store", records, values);
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("S1", values[0]);
		EXPECT_EQ("S1", values[1]);
		
		values.clear();
		
		// Now product		
		this->dimensions->Lookup("product", records, values);
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("P2", values[0]);
		EXPECT_EQ("P2", values[1]);		
	}
}
