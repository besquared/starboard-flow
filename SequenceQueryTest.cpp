/*
 *  SequenceQueryTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"
#include "SubwayFixture.h"

namespace {
	class SequenceQueryTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		SequenceQuery *query;
		SubwayFixture *subway;
		
		SequenceQueryTest() {}
		virtual ~SequenceQueryTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->subway = new SubwayFixture("/tmp/flow");
			this->query = new SequenceQuery("/tmp/flow");
			
			this->query->clusters->push_back("card-id");
			this->query->clusters->push_back("day");
			
			this->query->groupings->push_back("fare-group");
			this->query->groupings->push_back("day");
			
			this->query->conditions->gte("day", "20091209");
			
			shared_ptr<Conditions> x1(new Conditions); x1->eq("action", "in");
			this->query->pattern->push_back("station", "X", "x1", x1);
			
			shared_ptr<Conditions> y1(new Conditions); y1->eq("action", "out");
			this->query->pattern->push_back("station", "Y", "y1", y1);
			
			shared_ptr<Conditions> y2(new Conditions); y2->eq("action", "in");
			this->query->pattern->push_back("station", "Y", "y2", y2);
			
			shared_ptr<Conditions> x2(new Conditions); x2->eq("action", "out");
			this->query->pattern->push_back("station", "X", "x2", x2);			
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->query);
			delete(this->subway);
		}
	};
	
	TEST_F(SequenceQueryTest, MaterializesSingleTable) {		
		shared_ptr<Table> table(new Table());
		shared_ptr<Column> key(new TColumn<SequenceKey>);
		shared_ptr<Column> events(new TListColumn<SequenceEvent>);
		table->columns->push_back("key", key);		
		table->columns->push_back("events", events);
		
		Response materialized = this->query->Materialize(table);
		
		if(!materialized.get<0>()) {
			FAIL() << "Could not materialize single table";
		}
		
		
	}
}  // namespace
