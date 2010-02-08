/*
 *  SubstringTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/31/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>
#include <Engine/Sequential/Scanner/Substring.h>

namespace {
	using namespace Flow::Engine;
	
	class SubstringTest : public ::testing::Test {
	protected:
    vector<WorkSet> worksets;
    
		SubstringTest() {}
		virtual ~SubstringTest() {}
    
		virtual void SetUp() {
      map<string, string> values;
      values["store"] = "S1";
      values["season"] = "Fall";
      
      RIDList records;
      records.push_back(90);
      records.push_back(100);
      records.push_back(476);
      records.push_back(728);
      records.push_back(937);
      
      Engine::WorkSet workset(values, records);
      
      workset.dimensions["station"].push_back("montgomery");
      workset.dimensions["station"].push_back("montgomery");
      workset.dimensions["station"].push_back("17th street");
      workset.dimensions["station"].push_back("16th street");
      workset.dimensions["station"].push_back("montgomery");
      
      workset.dimensions["action"].push_back("in");
      workset.dimensions["action"].push_back("in");
      workset.dimensions["action"].push_back("out");
      workset.dimensions["action"].push_back("in");
      workset.dimensions["action"].push_back("out");
      
      worksets.push_back(workset);      
    }
		virtual void TearDown() {}
	};
	
	TEST_F(SubstringTest, MatchesSimpleSequences) {
    Conditions conditions1;
    Conditions conditions2;
    Conditions conditions3;
    Conditions conditions4;
    conditions1.Eq("action", "in");
    conditions2.Eq("action", "out");
    conditions3.Eq("action", "in");
    conditions4.Eq("action", "out");
    
    Sequential::Pattern pattern;
		pattern.push_back("station", "X", "x1", conditions1);
    pattern.push_back("station", "Y", "y1", conditions2);
    pattern.push_back("station", "Y", "y2", conditions3);
    pattern.push_back("station", "X", "x2", conditions4);
        
    Sequential::Matches matches;
    Sequential::Scanner::Substring scanner;
    scanner.execute(pattern, worksets, matches);
    
    ASSERT_EQ(1, matches.size());
    ASSERT_EQ(1, matches[0].size());
    EXPECT_EQ(0, matches[0][0].position);
	}
  
  TEST_F(SubstringTest, MatchesShiftingSequences) {
    Conditions conditions1;
    Conditions conditions2;
    Conditions conditions3;
    Conditions conditions4;
    conditions1.Eq("action", "in");
    conditions2.Eq("action", "out");
    conditions3.Eq("action", "in");
    conditions4.Eq("action", "out");
    
    Sequential::Pattern pattern;
		pattern.push_back("station", "X", "x1", conditions1);
    pattern.push_back("station", "Y", "y1", conditions2);
    pattern.push_back("station", "Y", "y2", conditions3);
    pattern.push_back("station", "X", "x2", conditions4);
        
    Sequential::Matches matches;
    Sequential::Scanner::Substring scanner;
    scanner.execute(pattern, worksets, matches);
    
    ASSERT_EQ(1, matches.size());
    ASSERT_EQ(1, matches[0].size());
    EXPECT_EQ(1, matches[0][0].position);
	}  

  TEST_F(SubstringTest, MatchesCompoundConditions) {
    Conditions conditions1;
    Conditions conditions2;
    Conditions conditions3;
    Conditions conditions4;
    conditions1.Eq("action", "in");
    conditions2.Eq("action", "out");
    conditions2.Eq("station", "16th street");
    conditions3.Eq("action", "in");
    conditions4.Eq("action", "out");
    
    Sequential::Pattern pattern;
		pattern.push_back("station", "X", "x1", conditions1);
    pattern.push_back("station", "Y", "y1", conditions2);
    pattern.push_back("station", "Y", "y2", conditions3);
    pattern.push_back("station", "X", "x2", conditions4);
        
    Sequential::Matches matches;
    Sequential::Scanner::Substring scanner;
    scanner.execute(pattern, worksets, matches);
    
    ASSERT_EQ(1, matches.size());
    ASSERT_EQ(1, matches[0].size());
    EXPECT_EQ(1, matches[0][0].position);
	}

  TEST_F(SubstringTest, MatchesCompoundConditionsWithNoMatches) {
    Conditions conditions1;
    Conditions conditions2;
    Conditions conditions3;
    Conditions conditions4;
    conditions1.Eq("action", "in");
    conditions2.Eq("action", "out");
    conditions2.Eq("station", "16th street");
    conditions3.Eq("action", "in");
    conditions4.Eq("action", "out");
    
    Sequential::Pattern pattern;
		pattern.push_back("station", "X", "x1", conditions1);
    pattern.push_back("station", "Y", "y1", conditions2);
    pattern.push_back("station", "Y", "y2", conditions3);
    pattern.push_back("station", "X", "x2", conditions4);
        
    Sequential::Matches matches;
    Sequential::Scanner::Substring scanner;
    scanner.execute(pattern, worksets, matches);
    
    ASSERT_EQ(0, matches.size());
	}  
}