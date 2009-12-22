/*
 *  ShellDimensionsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/27/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class ShellDimensionsTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		ShellDimensions *dimensions;
		ShellFragments *fragments;
		
		ShellDimensionsTest() {}
		virtual ~ShellDimensionsTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->fragments = new ShellFragments("/tmp/flow");
			this->fragments->database->Truncate();
			tuple<bool, string> opened = this->fragments->database->OpenWriter();
			
			if(!opened.get<0>()) {
				FAIL() << "Could not open fragments database for dimensions test";
			}
			
			this->dimensions = this->fragments->dimensions;
		}
				
		virtual void TearDown() {
			delete(this->helper);
			delete(this->fragments);
		}
	};
	
	TEST_F(ShellDimensionsTest, CreatesDimension) {
		Response created = this->dimensions->Create("1", "mydim");
		
		ASSERT_EQ(true, created.get<0>());
		
		// "[dimensions]" => "mydim"
		// "1:[dimensions]" => "mydim"
		// "[dimensions]:mydim" => "1"
		
		vector<string> alldims = this->fragments->database->GetList("[dimensions]");
		vector<string> fragdims = this->fragments->database->GetList("1:[dimensions]");
		string fragment = this->fragments->database->Get("[dimensions]:mydim");
		
		ASSERT_EQ(1, alldims.size());
		EXPECT_EQ("mydim", alldims[0]);
		
		ASSERT_EQ(1, fragdims.size());
		EXPECT_EQ("mydim", fragdims[0]);
		
		ASSERT_EQ("1", fragment);
	}
	
	TEST_F(ShellDimensionsTest, ListsDimensions) {
		this->dimensions->Create("1", "mydim");
		this->dimensions->Create("1", "mydim2");
		this->dimensions->Create("2", "mydim3");
		
		vector<string> dimensions = this->dimensions->List();
		
		ASSERT_EQ(3, dimensions.size());
		EXPECT_EQ("mydim", dimensions[0]);
		EXPECT_EQ("mydim2", dimensions[1]);
		EXPECT_EQ("mydim3", dimensions[2]);
		
		vector<string> frag1 = this->dimensions->List("1");
		
		ASSERT_EQ(2, frag1.size());
		EXPECT_EQ("mydim", frag1[0]);
		EXPECT_EQ("mydim2", frag1[1]);
		
		vector<string> frag2 = this->dimensions->List("2");
		
		ASSERT_EQ(1, frag2.size());
		EXPECT_EQ("mydim3", frag2[0]);
	}
	
	TEST_F(ShellDimensionsTest, InsertsValues) {
		this->dimensions->Create("1", "mydim");
		
		Response inserted;
		
		inserted = this->dimensions->Insert("mydim", "val1");
		ASSERT_EQ(true, inserted.get<0>());
		
		inserted = this->dimensions->Insert("mydim", "val2");
		ASSERT_EQ(true, inserted.get<0>());
		
		inserted = this->dimensions->Insert("mydim", "val1");
		ASSERT_EQ(true, inserted.get<0>());
		
		vector<string> values = this->fragments->database->GetList("[mydim]");
		
		ASSERT_EQ(2, values.size());
		EXPECT_EQ("val1", values[0]);
		EXPECT_EQ("val2", values[1]);
	}
	
	TEST_F(ShellDimensionsTest, ListsValues) {
		this->dimensions->Create("1", "mydim");
		this->dimensions->Create("1", "mydim2");

		this->dimensions->Insert("mydim", "val1");
		this->dimensions->Insert("mydim", "val2");
		this->dimensions->Insert("mydim2", "val1");

		vector<string> values1 = this->dimensions->Values("mydim");
		
		ASSERT_EQ(2, values1.size());
		EXPECT_EQ("val1", values1[0]);
		EXPECT_EQ("val2", values1[1]);
		
		vector<string> values2 = this->dimensions->Values("mydim2");
		
		ASSERT_EQ(1, values2.size());
		EXPECT_EQ("val1", values2[0]);
	}
}  // namespace
