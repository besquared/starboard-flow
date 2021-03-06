/*
 *  ConstructorTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 1/24/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>
#include <Engine/Pipeline/Constructor.h>

using namespace Testing::Domain;

namespace {
	using namespace Flow::Engine;
	
	class ConstructorTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		MockMeasures* measures;
		MockDimensions* dimensions;
		
		ConstructorTest() {}
		virtual ~ConstructorTest() {}
		
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
	
	TEST_F(ConstructorTest, PerformsPointConstruction) {
		Query::Analytical query;
		Pipeline::Constructor constructor;
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "Fall");
		
		RIDList records;
		records.push_back(1.0);
		records.push_back(2.0);
		
		map<string, string> specified;
		specified["store"] = "S1";
		specified["season"] = "Fall";
		
		EXPECT_CALL(*this->indices, Lookup(specified, _)).WillOnce(DoAll(SetArgReferee<1>(records), Return(true)));		
		
		vector<Engine::WorkSet> results;
		constructor.Execute(this->purchases, &query, results);
		
		ASSERT_EQ(1, results.size());
		ASSERT_EQ(2, results[0].records.size());
		ASSERT_EQ(2, results[0].values.size());
		EXPECT_EQ("S1", results[0].values["store"]);
		EXPECT_EQ("Fall", results[0].values["season"]);
	}
	
	TEST_F(ConstructorTest, PerformsHybridConstruction) {
		Query::Analytical query;
		Pipeline::Constructor constructor;
		query.conditions->Eq("store", "S1");
		query.conditions->Eq("season", "Fall");
		query.conditions->Gt("day", "20091020");
		
		RIDList records;
		records.push_back(1.0);
		records.push_back(2.0);
		
		map<string, string> specified;
		specified["store"] = "S1";
		specified["season"] = "Fall";
		
		set<string> inquired;
		inquired.insert("day");
		
		RIDTree days;
		RIDMap dayrecords;
		dayrecords["20091021"].push_back(1.0);
		dayrecords["20091021"].push_back(2.0);
		dayrecords["20091021"].push_back(3.0);
		days["day"] = dayrecords;
		
		EXPECT_CALL(*this->indices, Lookup(specified, _)).WillOnce(DoAll(SetArgReferee<1>(records), Return(true)));
		EXPECT_CALL(*this->indices, Lookup(inquired, _, _)).WillOnce(DoAll(SetArgReferee<2>(days), Return(true)));
		
		vector<Engine::WorkSet> results;
		constructor.Execute(this->purchases, &query, results);
		
		ASSERT_EQ(1, results.size());
		ASSERT_EQ(2, results[0].records.size()); // RID 1, 2

		ASSERT_EQ(3, results[0].values.size());
		EXPECT_EQ("20091021", results[0].values["day"]);
		EXPECT_EQ("S1", results[0].values["store"]);
		EXPECT_EQ("Fall", results[0].values["season"]);
	}
}