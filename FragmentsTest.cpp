/*
 *  FragmentsTest.cpp
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
	class FragmentsTest : public ::testing::Test {
	protected:
		Fragments* fragments;
		Mocks::MockMeta* meta;

		FragmentsTest() {}
		virtual ~FragmentsTest() {}
		
		virtual void SetUp() {
			string path = "/tmp/flow";
			this->meta = new Mocks::MockMeta(path);
			this->fragments = new Fragments(this->meta);
		}
		
		virtual void TearDown() {
			delete(this->meta);
			delete(this->fragments);
		}
	};
	
	TEST_F(FragmentsTest, InsertsRecords) {
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

		ASSERT_EQ(true, this->fragments->Insert(record, dimensions));
		// check this stuff
	}
	
//	TEST_F(FragmentsTest, LooksUpRecords) {
//		
//	}
}