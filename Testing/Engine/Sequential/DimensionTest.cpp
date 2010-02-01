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
    s1_fall.dimensions["station"].push_back("montgomery");
    s1_fall.dimensions["station"].push_back("16th Street");
    s1_fall.dimensions["station"].push_back("montgomery");
    
    ASSERT_EQ(true, dimension.match(s1_fall, 0));
    ASSERT_EQ(false, dimension.match(s1_fall, 1));
    ASSERT_EQ(true, dimension.match(s1_fall, 2));
  }
}  // namespace
