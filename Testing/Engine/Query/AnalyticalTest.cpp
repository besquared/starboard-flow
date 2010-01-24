/*
 *  QueryAnalyticalTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * +-------+----+----+--------+-------+
 * | Store | Product | Season | Sales |
 * +=======+=========+========|=======+
 * | S1    | P1      | s      | 6     |
 * +-------+---------+--------|-------+
 * | S1    | P2      | s      | 12    |
 * +-------+---------+--------+-------|
 * | S2    | P1      | f      | 9     |
 * +-------+---------+--------|-------|
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Testing/Engine/Executive/MockAnalytical.h>

using namespace ::Engine;
using namespace Testing::Domain;
using namespace Testing::Engine::Executive;

namespace {
	class QueryAnalyticalTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		
		QueryAnalyticalTest() {}
		virtual ~QueryAnalyticalTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
		}
		
		virtual void TearDown() {
			delete(this->purchases);
		}
	};
	
	TEST_F(QueryAnalyticalTest, ProvidesInstantiated) {
		Query::Analytical query;
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		map<string, string> instantiate;
		query.Instantiate(instantiate);

		ASSERT_EQ(1, instantiate.size());
		EXPECT_EQ("S1", instantiate["store"]);
	}
	
	TEST_F(QueryAnalyticalTest, ProvidesInstantiatedValues) {
		Query::Analytical query;
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		vector<string> instantiated_vals;
		query.InstantiatedValues(instantiated_vals);
		
		ASSERT_EQ(1, instantiated_vals.size());
		EXPECT_EQ("S1", instantiated_vals[0]);
	}
	
	TEST_F(QueryAnalyticalTest, ProvidesInquired) {
		Query::Analytical query;
		
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
	
	TEST_F(QueryAnalyticalTest, ProvidesDimensions) {
		Query::Analytical query;
		
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
