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
	
	TEST_F(ScannerTest, ScansAndAssignsSequences) {
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
        
    Pipeline::Scanner scanner;
    Sequential::Matches matches;
    scanner.Execute(this->purchases, &query, worksets, matches);
    
    // test for matches here
    ASSERT_EQ(1, matches.size());
    ASSERT_EQ(1, matches[0].size());
    EXPECT_EQ(1, matches[0][0].position);
    ASSERT_EQ(2, matches[0][0].tvalues.size());
    EXPECT_EQ("montgomery", matches[0][0].tvalues["X"]);
    EXPECT_EQ("16th street", matches[0][0].tvalues["Y"]);
	}	
}