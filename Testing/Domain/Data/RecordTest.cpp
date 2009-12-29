/*
 *  RecordTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

namespace {
	class RecordTest : public ::testing::Test {
	protected:
		RecordTest() {}
		virtual ~RecordTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(RecordTest, Initializes) {
		Record record(1);
		EXPECT_EQ(1, record.id);
	}
	
	TEST_F(RecordTest, GetsDimensions) {
		Record record(1);
		record["fare-group"] = "Regular";
		record["day"] = "20091219";
		
		set<string> dimensions = record.Dimensions();
		ASSERT_EQ(2, dimensions.size());
		EXPECT_EQ(1, dimensions.count("fare-group"));
		EXPECT_EQ(1, dimensions.count("day"));
	}
	
	TEST_F(RecordTest, GetsValues) {
		Record record(1);
		record["fare-group"] = "Regular";
		record["day"] = "20091219";
		record["year"] = "20091219";
		
		vector<string> values = record.Values();
		ASSERT_EQ(3, values.size());
		EXPECT_EQ("20091219", values[0]);
		EXPECT_EQ("Regular", values[1]);
		EXPECT_EQ("20091219", values[2]);
	}
	
	TEST_F(RecordTest, PartitionsRecord) {
		Record record(1);
		record["fare-group"] = "Regular";
		record["day"] = "20091219";
		record["year"] = "20091219";
		
		set<string> dimensions;
		dimensions.insert("day");
		dimensions.insert("fare-group");
		
		Record partition = record.Partition(dimensions);
		ASSERT_EQ(2, partition.size());
		EXPECT_EQ("20091219", partition["day"]);
		EXPECT_EQ("Regular", partition["fare-group"]);
	}
}