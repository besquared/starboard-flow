/*
 *  ExecutiveTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>

using namespace ::Engine;
using namespace Testing::Domain;

namespace {
	class ExecutiveTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		
		ExecutiveTest() {}
		virtual ~ExecutiveTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
			this->indices = (MockIndices*)(this->purchases->indices);
		}
		
		virtual void TearDown() {
			delete(this->purchases);
		}
	};
		
	TEST_F(ExecutiveTest, ExecutesPointQuery) {		
		Analytical::Query query;
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "Fall");
		query.aggregates->Count("records");
		query.aggregates->Sum("sales");
		
		Analytical::Executive executive(this->purchases, &query);
		
		RIDList records;
		records.push_back(1.0);
		records.push_back(2.0);
		
		map<string, string> specified;
		specified["store"] = "S1";
		specified["season"] = "Fall";

		EXPECT_CALL(*this->indices, Lookup(specified, _)).WillOnce(DoAll(SetArgReferee<1>(records), Return(true)));		
		
		Analytical::Groups results;
		executive.Execute(results);
		
		ASSERT_EQ(1, results.size());
		ASSERT_EQ(2, results[0].size());
		EXPECT_EQ(1, results[0][0]);
		EXPECT_EQ(2, results[0][1]);
		ASSERT_EQ(2, results.dimensions.size());
		EXPECT_EQ("store", results.dimensions[0]);
		EXPECT_EQ("season", results.dimensions[1]);
		ASSERT_EQ(2, results[0].values.size());
		EXPECT_EQ("S1", results[0].values[0]);
		EXPECT_EQ("Fall", results[0].values[1]);
	}
}  // namespace
