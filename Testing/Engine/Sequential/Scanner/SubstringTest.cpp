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
    Sequential::Pattern pattern;
		pattern.push_back("station", "X", "x1");
    pattern.push_back("station", "Y", "y1");
    pattern.push_back("station", "Y", "y2");
    pattern.push_back("station", "X", "x2");
    
    vector<string> values;
    values.push_back("S1");
    values.push_back("Fall");
    
    Engine::Groups haystack;
    Engine::Group s1_fall(values);
		s1_fall.records.push_back(1);
		s1_fall.records.push_back(2);
    s1_fall.records.push_back(3);
    s1_fall.records.push_back(4);
    s1_fall.records.push_back(5);
		haystack.push_back(s1_fall);
    
    Sequential::Scanner::Matches matches;
    
    Sequential::Scanner::Substring scanner;
//    scanner.execute(pattern, haystack, matches);
	}	
}