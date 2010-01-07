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
		Analytical::Groups results;
		Analytical::Query query;
		query.conditions->Eq("store", "S1");
		query.aggregates->Count("records");
		query.aggregates->Sum("sales");
		
		Analytical::Executive executive(this->purchases, &query);
		
		RIDList records;
		records.push_back(1.0);
		records.push_back(2.0);
		
		map<string, string> specified;
		specified["store"] = "S1";
		
		EXPECT_CALL(*this->indices, Lookup(specified, _)).WillOnce(DoAll(SetArgReferee<1>(records), Return(true)));		
		
		executive.Execute(results);
	}
}  // namespace
