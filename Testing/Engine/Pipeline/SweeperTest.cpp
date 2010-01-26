/*
 *  SweeperTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Pipeline/Sweeper.h>

using namespace Testing::Domain;

namespace {
	using namespace Flow::Engine;
	
	class SweeperTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		MockMeasures* measures;
		MockDimensions* dimensions;
		
		SweeperTest() {}
		virtual ~SweeperTest() {}
		
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
	
	TEST_F(SweeperTest, SweepsGroup) {
		Query::Analytical query;
		Pipeline::Sweeper sweeper;
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "Fall");
		query.aggregates->count("sales");
		
		vector<string> values;
		values.push_back("S1");
		values.push_back("Fall");
		
		Engine::Groups results;
		Engine::Group s1_fall(values);
		s1_fall.push_back(1);
		s1_fall.push_back(2);
		results.push_back(s1_fall);
		
		sweeper.Execute(this->purchases, &query, results);
		
		ASSERT_EQ(1, results.size());
		EXPECT_EQ(0, results[0].size());
	}	
}