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
		
		ScannerTest() {}
		virtual ~ScannerTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
			this->indices = (MockIndices*)(this->purchases->indices);
			this->measures = (MockMeasures*)(this->purchases->measures);
			this->dimensions = (MockDimensions*)(this->purchases->dimensions);
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
    query.pattern.push_back("station1", "X", "x1", conditions1);
    query.pattern.push_back("station2", "Y", "y1", conditions2);
    query.pattern.push_back("station3", "Y", "y2", conditions3);
    query.pattern.push_back("station4", "X", "x2", conditions4);
    
    vector<string> dims;
    dims.push_back("season");
    dims.push_back("fare-group");
    
		vector<string> values;
		values.push_back("Fall");
    values.push_back("Regular");
		
		Engine::Groups results(dims);
		Engine::Group fall_regular(values);
    fall_regular.records.push_back(90);
    fall_regular.records.push_back(100);
    fall_regular.records.push_back(476);
    fall_regular.records.push_back(728);
    fall_regular.records.push_back(937);
    
    fall_regular.dimensions["station"].push_back("montgomery");
    fall_regular.dimensions["station"].push_back("montgomery");
    fall_regular.dimensions["station"].push_back("16th street");
    fall_regular.dimensions["station"].push_back("16th street");
    fall_regular.dimensions["station"].push_back("montgomery");    
    
    fall_regular.dimensions["action"].push_back("in");
    fall_regular.dimensions["action"].push_back("in");
    fall_regular.dimensions["action"].push_back("out");
    fall_regular.dimensions["action"].push_back("in");
    fall_regular.dimensions["action"].push_back("out");
    
		results.push_back(fall_regular);
    
    Pipeline::Scanner scanner;
	}	
}