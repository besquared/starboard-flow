/*
 *  TableTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/30/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

using namespace Flow::Engine::Column;

namespace {
	class TableTest : public ::testing::Test {
	protected:
		TableTest() {}
		virtual ~TableTest() {}
		virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(TableTest, AddsColumns) {
		shared_ptr<Table> table(new Table());
		
		shared_ptr<Column::Base> store(new TColumn<string>("store"));
		table->push_back(store);
		
		shared_ptr<Column::Base> sales(new TColumn<double>("sales"));
		table->push_back(sales);
		
		shared_ptr<Column::Base> records(new TListColumn<RecordID>("records"));
		table->push_back(records);

		ASSERT_EQ(3, table->size());
	}
	
	TEST_F(TableTest, OverloadsVector) {
		shared_ptr<Table> table(new Table);
		
		shared_ptr< TColumn<string> > store(new TColumn<string>("store"));
		store->push_back("S1");
		store->push_back("S2");
		store->push_back("S3");
		shared_ptr<Column::Base> pstore = static_pointer_cast<Column::Base>(store);
		
		table->push_back(pstore);
		
		shared_ptr<Column::Base> cstore;
		if(table->size() >= 0) {
			cstore = table->at(0);
		} else {
			FAIL() << "Looking up store column failed";
		}

		shared_ptr< TColumn<string> > cpstore = 
			static_pointer_cast< TColumn<string> >(cstore);

		ASSERT_EQ(3, store->size());
		ASSERT_EQ(3, cpstore->size());
	}
}  // namespace
