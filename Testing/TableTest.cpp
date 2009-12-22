/*
 *  TableTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/30/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class TableTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		
		TableTest() {}
		virtual ~TableTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
		}
		
		virtual void TearDown() {
			delete(this->helper);
		}
	};
	
	TEST_F(TableTest, AddsColumns) {
		shared_ptr<Table> table(new Table());
		
		shared_ptr<Column> store(new TColumn<string>);
		table->columns->push_back("store", store);
		
		shared_ptr<Column> sales(new TColumn<double>);
		table->columns->push_back("sales", sales);
		
		shared_ptr<Column> records(new TListColumn<RecordID>);
		table->columns->push_back("records", records);

		ASSERT_EQ(3, table->columns->size());
	}
	
	TEST_F(TableTest, OverloadsVector) {
		shared_ptr<Table> table(new Table);
		
		shared_ptr< TColumn<string> > store(new TColumn<string>);
		store->push_back("S1");
		store->push_back("S2");
		store->push_back("S3");
		shared_ptr<Column> pstore = static_pointer_cast<Column>(store);
		
		table->columns->push_back("store", pstore);
		
		shared_ptr<Column> cstore;
		if(table->columns->size() >= 0) {
			cstore = table->columns->at(0);
		} else {
			FAIL() << "Looking up store column failed";
		}

		shared_ptr< TColumn<string> > cpstore = 
			static_pointer_cast< TColumn<string> >(cstore);

		ASSERT_EQ(3, store->size());
		ASSERT_EQ(3, cpstore->size());
	}
}  // namespace
