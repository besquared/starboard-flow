/*
 *  GathererTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Pipeline/Gatherer.h>

using namespace Testing::Domain;

namespace {
	using namespace Flow::Engine;
	
	class GathererTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		MockMeasures* measures;
		MockDimensions* dimensions;
		
		GathererTest() {}
		virtual ~GathererTest() {}
		
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
	
	TEST_F(GathererTest, GathersMeasures) {
		Query::Analytical query;
		Pipeline::Gatherer gatherer;
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
		
		EXPECT_CALL(*this->measures, Lookup("sales", s1_fall, _));
		
		gatherer.Execute(this->purchases, &query, results);
	}	
}