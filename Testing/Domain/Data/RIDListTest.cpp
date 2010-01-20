/*
 *  RIDListTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

namespace {
	using namespace Flow::Domain::Data;
	
	class RIDListTest : public ::testing::Test {
	protected:
		RIDListTest() {}
		virtual ~RIDListTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(RIDListTest, Initializes) {
		RIDList rlist;
		ASSERT_EQ(0, rlist.size());
	}
	
	TEST_F(RIDListTest, Intersects) {
		RIDList rlist1;
		rlist1.push_back(1);
		rlist1.push_back(2);
		rlist1.push_back(3);
		
		RIDList rlist2;
		rlist2.push_back(2);
		rlist2.push_back(3);
		rlist2.push_back(4);
		
		RIDList rlist3 = rlist1 & rlist2;
		
		ASSERT_EQ(2, rlist3.size());
		EXPECT_EQ(2, rlist3[0]);
		EXPECT_EQ(3, rlist3[1]);
	}
	
	TEST_F(RIDListTest, Merges) {
		RIDList rlist1;
		rlist1.push_back(1);
		rlist1.push_back(3);
		
		RIDList rlist2;
		rlist2.push_back(2);
		rlist2.push_back(6);
		
		RIDList rlist3 = rlist1 | rlist2;
		
		ASSERT_EQ(4, rlist3.size());
		EXPECT_EQ(1, rlist3[0]);
		EXPECT_EQ(2, rlist3[1]);
		EXPECT_EQ(3, rlist3[2]);
		EXPECT_EQ(6, rlist3[3]);
	}
}