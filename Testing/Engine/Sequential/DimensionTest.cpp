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
    
    map<string, string> values;
    values["store"] = "S1";
    values["season"] = "Fall";

    RIDList records;
    records.push_back(1.0);
    records.push_back(2.0);
    records.push_back(3.0);
    
    Engine::WorkSet workset(values, records);
    
    workset.dimensions["station"].push_back("montgomery");
    workset.dimensions["station"].push_back("16th Street");
    workset.dimensions["station"].push_back("montgomery");
    
    Sequential::Match match(0);

    ASSERT_EQ(true, dimension.match(workset, match, 0));
    ASSERT_EQ(false, dimension.match(workset, match, 1));
    ASSERT_EQ(true, dimension.match(workset, match, 2));
  }
  
  TEST_F(SequentialDimensionTest, MatchesMultipleGroupValues) {
    Conditions conditions;
    conditions.Eq("action", "in");
    conditions.Eq("station", "montgomery");
    Sequential::Dimension dimension("station", "X", "x1", conditions);

    map<string, string> values;
    values["store"] = "S1";
    values["season"] = "Fall";
    
    RIDList records;
    records.push_back(100.0);
    records.push_back(476.0);
    records.push_back(728.0);
    records.push_back(937.0);
    
    Engine::WorkSet workset(values, records);

    workset.dimensions["station"].push_back("montgomery");
    workset.dimensions["station"].push_back("16th street");
    workset.dimensions["station"].push_back("16th street");
    workset.dimensions["station"].push_back("montgomery");

    workset.dimensions["action"].push_back("in");
    workset.dimensions["action"].push_back("out");
    workset.dimensions["action"].push_back("in");
    workset.dimensions["action"].push_back("out");
    
    Sequential::Match match(0);
    
    ASSERT_EQ(true, dimension.match(workset, match, 0));
    ASSERT_EQ(false, dimension.match(workset, match, 1));
    ASSERT_EQ(false, dimension.match(workset, match, 2));
    ASSERT_EQ(false, dimension.match(workset, match, 3));
  }
}  // namespace
