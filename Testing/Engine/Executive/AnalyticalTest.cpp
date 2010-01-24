/*
 *  ExecutiveAnalyticalTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Executive/Analytical.h>
#include <Testing/Engine/Pipeline/MockConstructor.h>
#include <Testing/Engine/Pipeline/MockGatherer.h>
#include <Testing/Engine/Pipeline/MockAggregator.h>
#include <Testing/Engine/Pipeline/MockSweeper.h>

using namespace Testing::Domain;

namespace {
	using namespace Flow::Engine;
	
	class ExecutiveAnalyticalTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		MockMeasures* measures;
		MockDimensions* dimensions;
		
		ExecutiveAnalyticalTest() {}
		virtual ~ExecutiveAnalyticalTest() {}
		
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
	
	TEST_F(ExecutiveAnalyticalTest, ExecutesProperStages) {
	}
}  // namespace
