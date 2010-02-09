/*
 *  ScannerTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/2/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Pipeline/Scanner.h>

using namespace Testing::Domain;

namespace {
	using namespace Flow::Engine;
	
	class ScannerTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		MockMeasures* measures;
		MockDimensions* dimensions;
		
    vector<WorkSet> worksets;
    
		ScannerTest() {}
		virtual ~ScannerTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
			this->indices = (MockIndices*)(this->purchases->indices);
			this->measures = (MockMeasures*)(this->purchases->measures);
			this->dimensions = (MockDimensions*)(this->purchases->dimensions);
            
      map<string, string> values;
      values["season"] = "Fall";
      values["fare-group"] = "Regular";
      
      RIDList records;
      records.push_back(90);
      records.push_back(100);
      records.push_back(476);
      records.push_back(728);
      records.push_back(937);
      
      Engine::WorkSet workset(values, records);
            
      workset.dimensions["station"].push_back("montgomery");
      workset.dimensions["station"].push_back("montgomery");
      workset.dimensions["station"].push_back("16th street");
      workset.dimensions["station"].push_back("16th street");
      workset.dimensions["station"].push_back("montgomery");    
      
      workset.dimensions["action"].push_back("in");
      workset.dimensions["action"].push_back("in");
      workset.dimensions["action"].push_back("out");
      workset.dimensions["action"].push_back("in");
      workset.dimensions["action"].push_back("out");
      
      worksets.push_back(workset);      
		}
		
		virtual void TearDown() {
			delete(this->purchases);
		}
	};
	
	TEST_F(ScannerTest, ScansAndAssemblesMatchSet) {
    Query::Sequential query;
    
    Conditions conditions1;
    Conditions conditions2;
    Conditions conditions3;
    Conditions conditions4;
    conditions1.Eq("action", "in");
    conditions2.Eq("action", "out");
    conditions3.Eq("action", "in");
    conditions4.Eq("action", "out");
    
    query.aggregates->count("records");
    query.sequence_group_by.push_back("season");
    query.sequence_group_by.push_back("fare-group");    
    query.pattern.push_back("station", "X", "x1", conditions1);
    query.pattern.push_back("station", "Y", "y1", conditions2);
    query.pattern.push_back("station", "Y", "y2", conditions3);
    query.pattern.push_back("station", "X", "x2", conditions4);
    
    MatchSet matchset;
    Pipeline::Scanner scanner;
    scanner.Execute(this->purchases, &query, worksets, matchset);
    
    // test for matches here
    ASSERT_EQ(1, matchset.keys.size());
    
    ASSERT_EQ(4, matchset[matchset.keys[0]].values.size());
    EXPECT_EQ("montgomery", matchset[matchset.keys[0]].values["X"]);
    EXPECT_EQ("16th street", matchset[matchset.keys[0]].values["Y"]);
    EXPECT_EQ("Fall", matchset[matchset.keys[0]].values["season"]);
    EXPECT_EQ("Regular", matchset[matchset.keys[0]].values["fare-group"]);

    ASSERT_EQ(1, matchset[matchset.keys[0]].matches.size());
    EXPECT_EQ(1, matchset[matchset.keys[0]].matches[0].position);
    EXPECT_EQ(2, matchset[matchset.keys[0]].matches[0].tvalues.size());
    EXPECT_EQ("montgomery", matchset[matchset.keys[0]].matches[0].tvalues["X"]);
    EXPECT_EQ("16th street", matchset[matchset.keys[0]].matches[0].tvalues["Y"]);
	}
  
  TEST_F(ScannerTest, AssemblesComlexMatchSet) {
    // looking for complex match set grouping here, takes preferably 3 groups
    //  first two groups have patterns that go together, third is by itself
    // A,B,x1,y2 - A,B,x1,y2 - A,C,x1,y2
    
    map<string, string> values;
    values["season"] = "Fall";
    values["fare-group"] = "Regular";
    values["card-id"] = "00001";
    
    RIDList records1;
    records1.push_back(1.0);
    records1.push_back(2.0);
    records1.push_back(3.0);
    records1.push_back(4.0);
    
    Engine::WorkSet workset1(values, records1);
    workset1.dimensions["station"].push_back("montgomery");
    workset1.dimensions["station"].push_back("16th street");
    workset1.dimensions["station"].push_back("montgomery");
    workset1.dimensions["station"].push_back("16th street");
    
    RIDList records2;
    records2.push_back(5.0);
    records2.push_back(6.0);
    
    values["fare-group"] = "Senior";
    Engine::WorkSet workset2(values, records2);
    workset2.dimensions["station"].push_back("montgomery");
    workset2.dimensions["station"].push_back("16th street");
    
    worksets.clear();
    worksets.push_back(workset1);
    worksets.push_back(workset2);
    
    Query::Sequential query;
    query.aggregates->count("records");
    query.sequence_group_by.push_back("season");
    query.sequence_group_by.push_back("fare-group");    
    query.pattern.push_back("station", "X", "x1");
    query.pattern.push_back("station", "Y", "y1");
    
    MatchSet matchset;
    Pipeline::Scanner scanner;
    scanner.Execute(this->purchases, &query, worksets, matchset);
    
    for(size_t i = 0; i < matchset.keys.size(); i++) {
      cout << matchset[matchset.keys[i]] << endl;
    }
    
    ASSERT_EQ(3, matchset.keys.size());
    
    ASSERT_EQ(4, matchset[matchset.keys[0]].values.size());
    EXPECT_EQ("montgomery", matchset[matchset.keys[0]].values["X"]);
    EXPECT_EQ("16th street", matchset[matchset.keys[0]].values["Y"]);
    EXPECT_EQ("Fall", matchset[matchset.keys[0]].values["season"]);
    EXPECT_EQ("Regular", matchset[matchset.keys[0]].values["fare-group"]);
    EXPECT_EQ(2, matchset[matchset.keys[0]].matches.size());
    
    ASSERT_EQ(4, matchset[matchset.keys[1]].values.size());
    EXPECT_EQ("16th street", matchset[matchset.keys[1]].values["X"]);
    EXPECT_EQ("montgomery", matchset[matchset.keys[1]].values["Y"]);
    EXPECT_EQ("Fall", matchset[matchset.keys[1]].values["season"]);
    EXPECT_EQ("Regular", matchset[matchset.keys[1]].values["fare-group"]);
    EXPECT_EQ(1, matchset[matchset.keys[1]].matches.size());
    
    ASSERT_EQ(4, matchset[matchset.keys[2]].values.size());
    EXPECT_EQ("montgomery", matchset[matchset.keys[2]].values["X"]);
    EXPECT_EQ("16th street", matchset[matchset.keys[2]].values["Y"]);
    EXPECT_EQ("Fall", matchset[matchset.keys[2]].values["season"]);
    EXPECT_EQ("Senior", matchset[matchset.keys[2]].values["fare-group"]);
    EXPECT_EQ(1, matchset[matchset.keys[2]].matches.size());    
  }
}