/*
 *  IndicesTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include "MockMeta.h"
#include "MockIndex.h"

namespace Mocks = Testing::Database;

using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::_;

namespace {
	class IndicesTest : public ::testing::Test {
	protected:
		Indices* indices;
		Mocks::MockMeta* meta;
		Mocks::MockIndex* index;

		IndicesTest() {}
		virtual ~IndicesTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			this->meta = new Mocks::MockMeta(path);
			this->indices = new Indices(this->meta);
			this->index = (Mocks::MockIndex*)(this->meta->index);
		}
		
		virtual void TearDown() {
			delete(this->meta);
			delete(this->indices);
		}
	};
	
	TEST_F(IndicesTest, InsertsRecords) {		
		set<string> allocated;
		allocated.insert("card-id");
		allocated.insert("day");
		allocated.insert("district");
		allocated.insert("fare-group");
		allocated.insert("station");
		
		map<string, string> fragment1;
		map<string, string> fragment2;
		fragment1["card-id"] = "00000001";
		fragment1["day"] = "20091020";
		fragment1["district"] = "financial";
		fragment1["fare-group"] = "Regular";
		fragment2["station"] = "16th";
		
		EXPECT_CALL(*this->meta, OpenWriter()).WillOnce(Return(true));
		EXPECT_CALL(*this->meta, Allocate(allocated)).WillOnce(Return(true));
		EXPECT_CALL(*this->meta, OpenReader()).WillOnce(Return(true));
		EXPECT_CALL(*this->meta, Index("card-id", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		EXPECT_CALL(*this->meta, Index("day", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		EXPECT_CALL(*this->meta, Index("district", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		EXPECT_CALL(*this->meta, Index("fare-group", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		EXPECT_CALL(*this->meta, Index("station", _)).WillOnce(DoAll(SetArgReferee<1>("2"), Return(true)));
		EXPECT_CALL(*this->meta, Close()).Times(2).WillRepeatedly(Return(true));

		EXPECT_CALL(*this->index, OpenWriter()).WillOnce(Return(true));
		EXPECT_CALL(*this->index, Insert(fragment1)).WillOnce(Return(true));
		EXPECT_CALL(*this->index, Insert(fragment2)).WillOnce(Return(true));
		EXPECT_CALL(*this->index, Close()).WillOnce(Return(true));

		RecordID record = 1;
		map<string, string> row;
		row["card-id"] = "00000001";
		row["day"] = "20091020";
		row["district"] = "financial";
		row["fare-group"] = "Regular";
		row["station"] = "16th";
		
		ASSERT_EQ(true, this->indices->Insert(record, row));
	}
	
	TEST_F(IndicesTest, LooksUpRecords) {
		set<string> dimensions;
		dimensions.insert("day");
		dimensions.insert("fare-group");
		
		vector<Condition> conditions;
		
		EXPECT_CALL(*this->meta, OpenReader()).WillOnce(Return(true));
		EXPECT_CALL(*this->meta, Close()).Times(2).WillRepeatedly(Return(true));
		
		ASSERT_EQ(true, this->indices->Lookup(dimensions, conditions));
	}
}