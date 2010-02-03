/*
 *  DimensionTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Engine/Sequential/Dimension.h>

using namespace Flow::Engine;

namespace {
	class SequentialDimensionTest : public ::testing::Test {
	protected:
		SequentialDimensionTest() {}
		virtual ~SequentialDimensionTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(SequentialDimensionTest, Instantiates) {
		Sequential::Dimension dimension("station", "X", "x1");
		
		EXPECT_EQ("station", dimension.name);
		EXPECT_EQ("X", dimension.symbol);
		EXPECT_EQ("x1", dimension.alias);
	}
  
  TEST_F(SequentialDimensionTest, MatchesGroupValue) {
    Conditions conditions;
    conditions.Eq("station", "montgomery");
    Sequential::Dimension dimension("station", "X", "x1", conditions);

    vector<string> values;
    values.push_back("S1");
    values.push_back("Fall");
    Engine::Group s1_fall(values);
    
    s1_fall.records.push_back(1.0);
    s1_fall.records.push_back(2.0);
    s1_fall.records.push_back(3.0);
    s1_fall.dimensions["station"].push_back("montgomery");
    s1_fall.dimensions["station"].push_back("16th Street");
    s1_fall.dimensions["station"].push_back("montgomery");

    Sequential::Match match(0);

    ASSERT_EQ(true, dimension.match(s1_fall, match, 0));
    ASSERT_EQ(false, dimension.match(s1_fall, match, 1));
    ASSERT_EQ(true, dimension.match(s1_fall, match, 2));
  }
  
  TEST_F(SequentialDimensionTest, MatchesMultipleGroupValues) {
    Conditions conditions;
    conditions.Eq("action", "in");
    conditions.Eq("station", "montgomery");
    Sequential::Dimension dimension("station", "X", "x1", conditions);

    vector<string> values;
    values.push_back("S1");
    values.push_back("Fall");
    Engine::Group s1_fall(values);
    
    s1_fall.records.push_back(100.0);
    s1_fall.records.push_back(476.0);
    s1_fall.records.push_back(728.0);
    s1_fall.records.push_back(937.0);

    s1_fall.dimensions["station"].push_back("montgomery");
    s1_fall.dimensions["station"].push_back("16th street");
    s1_fall.dimensions["station"].push_back("16th street");
    s1_fall.dimensions["station"].push_back("montgomery");

    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("out");
    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("out");
    
    Sequential::Match match(0);
    
    ASSERT_EQ(true, dimension.match(s1_fall, match, 0));
    ASSERT_EQ(false, dimension.match(s1_fall, match, 1));
    ASSERT_EQ(false, dimension.match(s1_fall, match, 2));
    ASSERT_EQ(false, dimension.match(s1_fall, match, 3));
  }
}  // namespace
