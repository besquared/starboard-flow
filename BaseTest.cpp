/*
 *  BaseTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/5/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class BaseTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		Base *flow;
		
		BaseTest() {}
		virtual ~BaseTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->flow = new Base("/tmp/flow");
			this->flow->fragments->database->Truncate();
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->flow);
		}
	};
	
	TEST_F(BaseTest, InsertsRecord) {
		RecordID record = 1;
		
		map<string, string> dimensions;
		dimensions["store"] = "S1";
		dimensions["product"] = "P1";
		dimensions["season"] = "s";
		
		map<string, double> measures;
		measures["amount"] = 6.0;
		measures["tax_amount"] = 0.45;
		
		Response inserted;
		inserted = this->flow->Insert(record, dimensions, measures);
		
		ASSERT_EQ(true, inserted.get<0>());
		
		// Dimension Storage
		tuple< bool, string, shared_ptr<Dimension> > store;
		store = this->flow->dimensions->OpenReader("store");
		ASSERT_EQ(true, store.get<0>());
		EXPECT_EQ("S1", store.get<2>()->Get(1));
		
		tuple< bool, string, shared_ptr<Dimension> > product;
		product = this->flow->dimensions->OpenReader("product");
		ASSERT_EQ(true, product.get<0>());
		EXPECT_EQ("P1", product.get<2>()->Get(1));
		
		tuple< bool, string, shared_ptr<Dimension> > season;
		season = this->flow->dimensions->OpenReader("season");
		ASSERT_EQ(true, season.get<0>());
		EXPECT_EQ("s", season.get<2>()->Get(1));
		
		// Measure Storage
		tuple< bool, string, shared_ptr<Measure> > amount;
		amount = this->flow->measures->OpenReader("amount");
		ASSERT_EQ(true, amount.get<0>());
		EXPECT_EQ(6.0, amount.get<2>()->Get(1));
		
		tuple< bool, string, shared_ptr<Measure> > tax_amount;
		tax_amount = this->flow->measures->OpenReader("tax_amount");
		ASSERT_EQ(true, tax_amount.get<0>());
		EXPECT_EQ(0.45, tax_amount.get<2>()->Get(1));
		
		// Indexing
		Instantiated instantiated;
		this->flow->fragments->OpenReader();
		this->flow->fragments->Lookup(dimensions, instantiated);
		this->flow->fragments->Close();
		
		ASSERT_EQ(1, instantiated.size());
		EXPECT_EQ(1, instantiated[0]);
	}
}  // namespace
