/*
 *  QueryTest.cpp
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
#include <Testing/Engine/Analytical/MockExecutive.h>

using namespace ::Engine;
using namespace Testing::Domain;
using namespace Testing::Engine::Analytical;

namespace {
	class QueryTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		
		QueryTest() {}
		virtual ~QueryTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
			this->indices = (MockIndices*)(this->purchases->indices);
		}
		
		virtual void TearDown() {
			delete(this->purchases);
		}
	};
	
	TEST_F(QueryTest, ProvidesInstantiated) {
		Analytical::Query query(this->purchases);
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		map<string, string> instantiate;
		query.Instantiate(instantiate);

		EXPECT_EQ(1, instantiate.size());
		EXPECT_EQ("S1", instantiate["store"]);
	}
	
	TEST_F(QueryTest, ProvidesInquired) {
		Analytical::Query query(this->purchases);
		
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "?");
		query.conditions->Lt("age", "00000015");
		
		set<string> inquire;
		Conditions conditions;
		query.Inquire(inquire, conditions);
		
		EXPECT_EQ(2, inquire.size());
		EXPECT_EQ(1, inquire.count("season"));
		EXPECT_EQ(1, inquire.count("age"));
		
		EXPECT_EQ(2, conditions.size());
	}
	
	TEST_F(QueryTest, ExecutesQuery) {
//		map<string, string> specified;
//		specified["store"] = "S1";
//		
//		::Domain::Data::RIDList records;
//		records.push_back(1.0);
//		records.push_back(2.0);
//		
//		EXPECT_CALL(*this->indices, Lookup(specified, _)).WillOnce(DoAll(SetArgReferee<1>(records), Return(true)));
		
		Engine::Analytical::Groups results;
		Analytical::Query query(this->purchases);
		
		MockExecutive executive(&query);
		EXPECT_CALL(executive, Execute(results)).WillOnce(Return(true));
		
		query.conditions->Eq("store", "S1");
		query.aggregates->Count("records");
		query.aggregates->Sum("sales");
		query.Execute(executive, results);
	}
	
//	TEST_F(QueryTest, ProcessesPurePointQuery) {
//	}
//
//	TEST_F(QueryTest, ProcessesPureRangeQuery) {
//	}
//
//	TEST_F(QueryTest, ProcessesMixedQuery) {
//	}	
//	
//	TEST_F(QueryTest, ProcessesQueryWithNoResults) {
//	}
}  // namespace
