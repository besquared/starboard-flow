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
		SubstringTest() {}
		virtual ~SubstringTest() {}
		virtual void SetUp() {}
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
		pattern.push_back("station1", "X", "x1", conditions1);
    pattern.push_back("station2", "Y", "y1", conditions2);
    pattern.push_back("station3", "Y", "y2", conditions3);
    pattern.push_back("station4", "X", "x2", conditions4);
    
    vector<string> values;
    values.push_back("S1");
    values.push_back("Fall");
    Engine::Group s1_fall(values);
    
    s1_fall.records.push_back(100);
    s1_fall.records.push_back(476);
    s1_fall.records.push_back(728);
    s1_fall.records.push_back(937);
    
    s1_fall.dimensions["station"].push_back("montgomery");
    s1_fall.dimensions["station"].push_back("16th street");
    s1_fall.dimensions["station"].push_back("16th street");
    s1_fall.dimensions["station"].push_back("montgomery");
    
    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("out");
    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("out");
    
    Engine::Groups sequences;
		sequences.push_back(s1_fall);
    
    Sequential::Scanner::Matches matches;
    Sequential::Scanner::Substring scanner;
    scanner.execute(pattern, sequences, matches);
    
    ASSERT_EQ(1, matches.matches.size());
    ASSERT_EQ(1, matches.matches[0].size());
    EXPECT_EQ(0, matches.matches[0][0]);
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
		pattern.push_back("station1", "X", "x1", conditions1);
    pattern.push_back("station2", "Y", "y1", conditions2);
    pattern.push_back("station3", "Y", "y2", conditions3);
    pattern.push_back("station4", "X", "x2", conditions4);
    
    vector<string> values;
    values.push_back("S1");
    values.push_back("Fall");
    Engine::Group s1_fall(values);
    
    s1_fall.records.push_back(90);
    s1_fall.records.push_back(100);
    s1_fall.records.push_back(476);
    s1_fall.records.push_back(728);
    s1_fall.records.push_back(937);
    
    s1_fall.dimensions["station"].push_back("montgomery");
    s1_fall.dimensions["station"].push_back("montgomery");
    s1_fall.dimensions["station"].push_back("16th street");
    s1_fall.dimensions["station"].push_back("16th street");
    s1_fall.dimensions["station"].push_back("montgomery");
    
    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("out");
    s1_fall.dimensions["action"].push_back("in");
    s1_fall.dimensions["action"].push_back("out");
    
    Engine::Groups sequences;
		sequences.push_back(s1_fall);
    
    Sequential::Scanner::Matches matches;
    Sequential::Scanner::Substring scanner;
    scanner.execute(pattern, sequences, matches);
    
    ASSERT_EQ(1, matches.matches.size());
    ASSERT_EQ(1, matches.matches[0].size());
    EXPECT_EQ(1, matches.matches[0][0]);
	}  
}