/*
 *  QueryTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Query/Sequential.h>

using namespace Flow::Engine;
using namespace Testing::Domain;

namespace {
	class QuerySequentialTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		
		QuerySequentialTest() {}
		virtual ~QuerySequentialTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
		}
		
		virtual void TearDown() {
			delete(this->purchases);
		}
	};
	
	TEST_F(QuerySequentialTest, ProvidesUniqMeasures) {
		Query::Sequential query;
		
		query.aggregates->sum("store");
		
		set<string> measures;
		query.Measures(measures);
		
		ASSERT_EQ(1, measures.size());
		EXPECT_EQ(1, measures.count("store"));
	}
	
	TEST_F(QuerySequentialTest, ProvidesInstantiated) {
		Query::Sequential query;
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		map<string, string> instantiate;
		query.Instantiate(instantiate);
    
		ASSERT_EQ(1, instantiate.size());
		EXPECT_EQ("S1", instantiate["store"]);
	}
	
	TEST_F(QuerySequentialTest, ProvidesInstantiatedValues) {
		Query::Sequential query;
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		vector<string> instantiated_vals;
		query.InstantiatedValues(instantiated_vals);
		
		ASSERT_EQ(1, instantiated_vals.size());
		EXPECT_EQ("S1", instantiated_vals[0]);
	}
	
	TEST_F(QuerySequentialTest, ProvidesInquired) {
		Query::Sequential query;
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		set<string> inquire;
		Conditions conditions;
		query.Inquire(inquire, conditions);
		
		ASSERT_EQ(2, inquire.size());
		EXPECT_EQ(1, inquire.count("season"));
		EXPECT_EQ(1, inquire.count("age"));
		
		EXPECT_EQ(2, conditions.size());
	}
	
	TEST_F(QuerySequentialTest, ProvidesDimensions) {
		Query::Sequential query;
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		vector<string> inquired;
		vector<string> instantiated;
		query.Dimensions(instantiated, inquired);
		
		ASSERT_EQ(2, inquired.size());
		EXPECT_EQ("season", inquired[0]);
		EXPECT_EQ("age", inquired[1]);
		
		ASSERT_EQ(1, instantiated.size());
		EXPECT_EQ("store", instantiated[0]);
	}
}  // namespace
