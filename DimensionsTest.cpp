/*
 *  DimensionsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

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
		
		vector<string> results;
		
		// Check store first
		Dimension store("/tmp/flow", "sales");
		ASSERT_EQ(true, store.OpenReader());
		
		store.Lookup(records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ("S1", results[0]);
		EXPECT_EQ("S1", results[1]);
		
		results.clear();
		
		// Now product		
		Dimension product("/tmp/flow", "sales");
		ASSERT_EQ(true, product.OpenReader());

		product.Lookup(records, results);
		ASSERT_EQ(2, results.size());
		EXPECT_EQ("P2", results[0]);
		EXPECT_EQ("P2", results[1]);		
	}
}
