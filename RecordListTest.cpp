/*
 *  RecordListTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class RecordListTest : public ::testing::Test {
	protected:
		RecordListTest() {}
		virtual ~RecordListTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(RecordListTest, InitializesWithEmptyConstructor) {
		RecordList records;
		ASSERT_EQ(0, records.size());
		ASSERT_EQ(4, records.capacity());
	}
	
	TEST_F(RecordListTest, AssignsAnArray) {
		RecordID* records = (RecordID*)malloc(4 * sizeof(RecordID));
		*(records) = 1.0;
		*(records + 1) = 2.0;
		*(records + 2) = 3.0;
		*(records + 3) = 4.0;
		
		RecordList rlist;
		rlist.assign(records, (size_t)4);
		
		ASSERT_EQ(4, rlist.size());
		EXPECT_EQ(1.0, rlist[0]);
		EXPECT_EQ(2.0, rlist[1]);
		EXPECT_EQ(3.0, rlist[2]);
		EXPECT_EQ(4.0, rlist[3]);

		free(records);
	}
	
	TEST_F(RecordListTest, AssignsFromVoidPointer) {
		size_t msize = 4 * sizeof(RecordID);
		
		RecordID* records = (RecordID*)malloc(msize);
		*(records) = 1.0;
		*(records + 1) = 2.0;
		*(records + 2) = 3.0;
		*(records + 3) = 4.0;
		
		RecordList rlist;
		rlist.assign((void*)records, (int)msize);
		
		ASSERT_EQ(4, rlist.size());
		EXPECT_EQ(1.0, rlist[0]);
		EXPECT_EQ(2.0, rlist[1]);
		EXPECT_EQ(3.0, rlist[2]);
		EXPECT_EQ(4.0, rlist[3]);
		
		free(records);		
	}
	
	TEST_F(RecordListTest, Copies) {
		
	}
}