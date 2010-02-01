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
		
		vector<string> values;
		values.push_back("S1");
		values.push_back("Fall");
		
		Engine::Groups results;
		Engine::Group s1_fall(values);
		results.push_back(s1_fall);
		results.back().records.push_back(1);
		results.back().records.push_back(2);
		results.back().measures["sales"].push_back(100);
		results.back().measures["sales"].push_back(250);
		
		aggregator.Execute(this->purchases, &query, results);
		
		ASSERT_EQ(2, results.back().aggregates["count_sales"]);
		ASSERT_EQ(350, results.back().aggregates["sum_sales"]);
	}	
}