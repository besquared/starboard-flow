/*
 *  AggregatorTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Pipeline/Aggregator.h>

using namespace Testing::Domain;

namespace {
	using namespace Flow::Engine;
	
	class AggregatorTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		MockMeasures* measures;
		MockDimensions* dimensions;
		
		AggregatorTest() {}
		virtual ~AggregatorTest() {}
		
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
	
	TEST_F(AggregatorTest, AggregatesMeasures) {
		Query::Analytical query;
		Pipeline::Aggregator aggregator;
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "Fall");
		query.aggregates->count("sales");
		query.aggregates->sum("sales");
		
		map<string, string> values;
    values["store"] = "S1";
    values["season"] = "Fall";
		
    RIDList records;
    records.push_back(1.0);
    records.push_back(2.0);
    
    Engine::WorkSet workset(values, records);
		workset.measures["sales"].push_back(100);
		workset.measures["sales"].push_back(250);
		
    vector<Engine::WorkSet> worksets;
    worksets.push_back(workset);
    
		aggregator.Execute(this->purchases, &query, worksets);
		
		ASSERT_EQ(2, worksets.back().aggregates["count_sales"]);
		ASSERT_EQ(350, worksets.back().aggregates["sum_sales"]);
	}
  
 	TEST_F(AggregatorTest, AggregatesMatchsets) {
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
    
    
  } 
}