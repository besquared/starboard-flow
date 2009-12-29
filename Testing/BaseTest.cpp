/*
 *  BaseTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/5/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>

namespace {
	class BaseTest : public ::testing::Test {
	protected:
		Base *flow;
		
		BaseTest() {}
		virtual ~BaseTest() {}
		
		virtual void SetUp() {
		}
		
		virtual void TearDown() {
		}
	};
	
//	TEST_F(BaseTest, InsertsRecord) {
//		Record record(1);
//		record["store"] = "S1";
//		record["product"] = "P1";
//		record["season"] = "s";
//		
//		map<string, double> measures;
//		measures["amount"] = 6.0;
//		measures["tax_amount"] = 0.45;
//		
//		ASSERT_EQ(true, this->flow->Insert(record, measures));
//		
//		// Dimension Storage
//		Dimension store;
//		store = this->flow->dimensions->OpenReader("store");
//		ASSERT_EQ(true, store.get<0>());
//		EXPECT_EQ("S1", store.get<2>()->Get(1));
//		
//		tuple< bool, string, shared_ptr<Dimension> > product;
//		product = this->flow->dimensions->OpenReader("product");
//		ASSERT_EQ(true, product.get<0>());
//		EXPECT_EQ("P1", product.get<2>()->Get(1));
//		
//		tuple< bool, string, shared_ptr<Dimension> > season;
//		season = this->flow->dimensions->OpenReader("season");
//		ASSERT_EQ(true, season.get<0>());
//		EXPECT_EQ("s", season.get<2>()->Get(1));
//		
//		// Measure Storage
//		tuple< bool, string, shared_ptr<Measure> > amount;
//		amount = this->flow->measures->OpenReader("amount");
//		ASSERT_EQ(true, amount.get<0>());
//		EXPECT_EQ(6.0, amount.get<2>()->Get(1));
//		
//		tuple< bool, string, shared_ptr<Measure> > tax_amount;
//		tax_amount = this->flow->measures->OpenReader("tax_amount");
//		ASSERT_EQ(true, tax_amount.get<0>());
//		EXPECT_EQ(0.45, tax_amount.get<2>()->Get(1));
//		
//		// Indexing
//		Instantiated instantiated;
//		this->flow->fragments->OpenReader();
//		this->flow->fragments->Lookup(dimensions, instantiated);
//		this->flow->fragments->Close();
//		
//		ASSERT_EQ(1, instantiated.size());
//		EXPECT_EQ(1, instantiated[0]);
//	}
}  // namespace
