/*
 *  MasterTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class MasterTest : public ::testing::Test {
	protected:
		Master* database;
		
		MasterTest() {}
		virtual ~MasterTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			
			Master::Create(path);
			database = new Master(path);
			
			this->database->Truncate();
			
			if(!this->database->OpenWriter()) {
				FAIL() << "Could not open database for MasterTest => " << this->database->Error() << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(MasterTest, AllocatesFragmentsAndDimensions) {
		set<string> dimensions;
		dimensions.insert("name");
		dimensions.insert("fare-group");
		dimensions.insert("card-id");
				
		ASSERT_EQ(true, this->database->Allocate(dimensions));

		dimensions.insert("day");
		dimensions.insert("station");
		dimensions.insert("district");
		dimensions.insert("action");
		
		ASSERT_EQ(true, this->database->Allocate(dimensions));

		set<string> retrieved;
		ASSERT_EQ(true, this->database->Dimensions(retrieved));
		
		ASSERT_EQ(7, retrieved.size());
		EXPECT_EQ(1, retrieved.count("name"));
		EXPECT_EQ(1, retrieved.count("fare-group"));
		EXPECT_EQ(1, retrieved.count("card-id"));
		EXPECT_EQ(1, retrieved.count("day"));
		EXPECT_EQ(1, retrieved.count("station"));
		EXPECT_EQ(1, retrieved.count("district"));
		EXPECT_EQ(1, retrieved.count("action"));
		
		vector<string> fragments;
		ASSERT_EQ(true, this->database->Fragments(fragments));
		
		ASSERT_EQ(2, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		EXPECT_EQ("2", fragments[1]);
		
		set<string> fragment1;
		ASSERT_EQ(true, this->database->Dimensions("1", fragment1));
		
		ASSERT_EQ(4, fragment1.size());
		EXPECT_EQ(1, fragment1.count("name"));
		EXPECT_EQ(1, fragment1.count("fare-group"));
		EXPECT_EQ(1, fragment1.count("card-id"));
		EXPECT_EQ(1, fragment1.count("action"));
		
		set<string> fragment2;
		ASSERT_EQ(true, this->database->Dimensions("2", fragment2));
		
		ASSERT_EQ(3, fragment2.size());
		EXPECT_EQ(1, fragment2.count("day"));
		EXPECT_EQ(1, fragment2.count("district"));
		EXPECT_EQ(1, fragment2.count("station"));
		
		string fragment;
		
		ASSERT_EQ(true, this->database->Fragment("name", fragment));
		EXPECT_EQ("1", fragment);
		
		ASSERT_EQ(true, this->database->Fragment("fare-group", fragment));
		EXPECT_EQ("1", fragment);
		
		ASSERT_EQ(true, this->database->Fragment("card-id", fragment));
		EXPECT_EQ("1", fragment);
		
		ASSERT_EQ(true, this->database->Fragment("action", fragment));
		EXPECT_EQ("1", fragment);

		ASSERT_EQ(true, this->database->Fragment("day", fragment));
		EXPECT_EQ("2", fragment);

		ASSERT_EQ(true, this->database->Fragment("district", fragment));
		EXPECT_EQ("2", fragment);

		ASSERT_EQ(true, this->database->Fragment("station", fragment));
		EXPECT_EQ("2", fragment);
	}	
}