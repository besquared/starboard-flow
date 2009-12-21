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
		
		ValueMap fragment1;
		ValueMap fragment2;
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
		
		Record record(1);
		record["card-id"] = "00000001";
		record["day"] = "20091020";
		record["district"] = "financial";
		record["fare-group"] = "Regular";
		record["station"] = "16th";
		
		ASSERT_EQ(true, this->indices->Insert(record));
	}
	
	TEST_F(IndicesTest, PerformsBasicLookup) {
		ValuesMap values;
		vector<string> days;
		vector<string> faregroups;
		days.push_back("20091220");
		days.push_back("20091219");
		faregroups.push_back("Regular");
		values["day"] = days;
		values["fare-group"] = faregroups;
		
		vector<string> sorteddays = days;
		sort(sorteddays.begin(), sorteddays.end());
		
		RIDList rids;
		RIDMap dayrids;
		RIDMap faregrouprids;
		rids.push_back(1);
		rids.push_back(2);
		dayrids["20091219"] = rids;
		dayrids["20091220"] = rids;
		faregrouprids["Regular"] = rids;
		
		set<string> dimensions;
		dimensions.insert("day");
		dimensions.insert("fare-group");
		
		EXPECT_CALL(*this->index, OpenReader()).WillOnce(Return(true));
		EXPECT_CALL(*this->index, Lookup(dimensions, _)).WillOnce(DoAll(SetArgReferee<1>(values), Return(true)));
		EXPECT_CALL(*this->index, Lookup("day", sorteddays, _)).WillOnce(DoAll(SetArgReferee<2>(dayrids), Return(true)));
		EXPECT_CALL(*this->index, Lookup("fare-group", faregroups, _)).WillOnce(DoAll(SetArgReferee<2>(faregrouprids), Return(true)));
		EXPECT_CALL(*this->index, Close()).WillOnce(Return(true));
		
		RIDTree records;
		Conditions conditions;
		ASSERT_EQ(true, this->indices->Lookup(dimensions, conditions, records));
		
		ASSERT_EQ(2, records.size());
		ASSERT_EQ(2, records["day"].size());
		EXPECT_EQ(2, records["day"]["20091219"].size());
		EXPECT_EQ(2, records["day"]["20091220"].size());
		ASSERT_EQ(1, records["fare-group"].size());
		EXPECT_EQ(2, records["fare-group"]["Regular"].size());
	}
}