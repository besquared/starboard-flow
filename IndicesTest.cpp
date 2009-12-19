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

namespace Mocks = Testing::Database;

using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::_;

namespace {
	class IndicesTest : public ::testing::Test {
	protected:
		Indices* indices;
		Mocks::MockMeta* meta;

		IndicesTest() {}
		virtual ~IndicesTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			this->meta = new Mocks::MockMeta(path);
			this->indices = new Indices(this->meta);
		}
		
		virtual void TearDown() {
			delete(this->meta);
			delete(this->indices);
		}
	};
	
	TEST_F(IndicesTest, InsertsRecords) {
		RecordID record = 1;
		map<string, string> dimensions;
		dimensions["day"] = "20091020";
		dimensions["fare-group"] = "Regular";
		dimensions["station"] = "16th";
		
		set<string> allocated;
		allocated.insert("day");
		allocated.insert("fare-group");
		allocated.insert("station");
		
		EXPECT_CALL(*this->meta, OpenWriter()).WillOnce(Return(true));
		EXPECT_CALL(*this->meta, Allocate(allocated)).WillOnce(Return(true));
		
		EXPECT_CALL(*this->meta, Fragment("day", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		EXPECT_CALL(*this->meta, Fragment("fare-group", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		EXPECT_CALL(*this->meta, Fragment("station", _)).WillOnce(DoAll(SetArgReferee<1>("1"), Return(true)));
		
		EXPECT_CALL(*this->meta, Close()).WillOnce(Return(true));

		ASSERT_EQ(true, this->indices->Insert(record, dimensions));
		// check this stuff
	}
	
//	TEST_F(IndicesTest, LooksUpRecords) {
//		
//	}
}