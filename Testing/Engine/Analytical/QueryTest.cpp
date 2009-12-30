/*
 *  QueryTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <Testing/TestHelper.h>
#include <Testing/Domain/MockBase.h>

using namespace ::Engine;
using namespace Testing::Domain;

namespace {
	class QueryTest : public ::testing::Test {
	protected:
		MockBase* purchases;
		MockIndices* indices;
		
		QueryTest() {}
		virtual ~QueryTest() {}
		
		virtual void SetUp() {
			this->purchases = new MockBase("/tmp/flow", "/tmp/flow");
			this->indices = (MockIndices*)(this->purchases->indices);
		}
		
		virtual void TearDown() {
			delete(this->purchases);
		}
	};
	
	/*
	 * +-------+----+----+--------+-------+
	 * | Store | Product | Season | Sales |
	 * +=======+=========+========|=======+
	 * | S1    | P1      | s      | 6     |
	 * +-------+---------+--------|-------+
	 * | S1    | P2      | s      | 12    |
	 * +-------+---------+--------+-------|
	 * | S2    | P1      | f      | 9     |
	 * +-------+---------+--------|-------|
	 */
	
	TEST_F(QueryTest, ProcessesPurePointQuery) {
		map<string, string> specified;
		specified["store"] = "S1";
		
		::Domain::Data::RIDList records;
		records.push_back(1.0);
		records.push_back(2.0);
		
		EXPECT_CALL(*this->indices, Lookup(specified, _)).WillOnce(DoAll(SetArgReferee<1>(records), Return(true)));
		
		Engine::Table results;
		Analytical::Query query(this->purchases);
		query.conditions->Eq("store", "S1");
		query.aggregates->Count("records");
		query.aggregates->Sum("sales");
		query.Execute(results);
	}
	
//	TEST_F(QueryTest, ProcessesPurePointQuery) {
//		this->LoadProductData();
//		
//		shared_ptr<Query> query(new Query(this->fragments, this->measures));
//		query->conditions->eq("store", "S1");
//		
//		shared_ptr<Aggregation> record_count(new COUNT("records"));
//		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
//		query->aggregations->push_back(record_count);
//		query->aggregations->push_back(sales_sum);
//		
//		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
//		
//		if(!executed.get<0>()) {
//			FAIL() << "Query execution failed: " << executed.get<1>();
//		}
//		
//		shared_ptr<Table> table = executed.get<2>();
//				
//		shared_ptr< TListColumn<string> > values_column = 
//		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
//		
//		vector<string> values;
//		ASSERT_EQ(1, values_column->size());
//		
//		values = values_column->at(0);
//		ASSERT_EQ(1, values.size());
//		EXPECT_EQ("S1", values[0]);
//		
//		shared_ptr< TColumn<double> > count_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
//		
//		ASSERT_EQ(1, count_column->size());
//		EXPECT_EQ(2, count_column->at(0));
//		
//		shared_ptr< TColumn<double> > sum_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
//		
//		ASSERT_EQ(1, sum_column->size());
//		EXPECT_EQ(18, sum_column->at(0));
//	}
//
//	TEST_F(QueryTest, ProcessesPureRangeQuery) {
//		this->LoadProductData();
//		
//		shared_ptr<Query> query(new Query(this->fragments, this->measures));
//		query->conditions->eq("store", "?");
//		
//		shared_ptr<Aggregation> record_count(new COUNT("records"));
//		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
//		query->aggregations->push_back(record_count);
//		query->aggregations->push_back(sales_sum);
//		
//		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
//		
//		if(!executed.get<0>()) {
//			FAIL() << "Query execution failed: " << executed.get<1>();
//		}
//		
//		shared_ptr<Table> table = executed.get<2>();
//		
//		shared_ptr< TListColumn<string> > values_column = 
//		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
//		
//		vector<string> values;
//		ASSERT_EQ(2, values_column->size());
//		
//		values = values_column->at(0);
//		ASSERT_EQ(1, values.size());
//		EXPECT_EQ("S1", values[0]);
//		
//		values = values_column->at(1);
//		ASSERT_EQ(1, values.size());
//		EXPECT_EQ("S2", values[0]);
//		
//		shared_ptr< TColumn<double> > count_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
//		
//		ASSERT_EQ(2, count_column->size());
//		EXPECT_EQ(2, count_column->at(0));
//		EXPECT_EQ(1, count_column->at(1));
//
//		shared_ptr< TColumn<double> > sum_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
//		
//		ASSERT_EQ(2, sum_column->size());
//		EXPECT_EQ(18, sum_column->at(0));
//		EXPECT_EQ(9, sum_column->at(1));
//	}
//
//	TEST_F(QueryTest, ProcessesMixedQuery) {
//		this->LoadProductData();
//		
//		shared_ptr<Query> query(new Query(this->fragments, this->measures));
//		query->conditions->eq("store", "S1");
//		query->conditions->eq("product", "?");
//		query->conditions->eq("season", "?");
//		
//		shared_ptr<Aggregation> record_count(new COUNT("records"));
//		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
//		query->aggregations->push_back(record_count);
//		query->aggregations->push_back(sales_sum);
//		
//		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
//		
//		if(!executed.get<0>()) {
//			FAIL() << "Query execution failed: " << executed.get<1>();
//		}
//		
//		shared_ptr<Table> table = executed.get<2>();
//				
//		shared_ptr< TListColumn<string> > values_column = 
//		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
//		
//		vector<string> values;
//		ASSERT_EQ(2, values_column->size());
//		
//		values = values_column->at(0);
//		ASSERT_EQ(3, values.size());
//		EXPECT_EQ("S1", values[0]);
//		EXPECT_EQ("P1", values[1]);
//		EXPECT_EQ("s", values[2]);
//		
//		values = values_column->at(1);
//		ASSERT_EQ(3, values.size());
//		EXPECT_EQ("S1", values[0]);
//		EXPECT_EQ("P2", values[1]);
//		EXPECT_EQ("s", values[2]);
//				
//		shared_ptr< TColumn<double> > count_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
//		
//		ASSERT_EQ(2, count_column->size());
//		EXPECT_EQ(1, count_column->at(0));
//		EXPECT_EQ(1, count_column->at(1));
//		
//		shared_ptr< TColumn<double> > sum_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
//		
//		ASSERT_EQ(2, sum_column->size());
//		EXPECT_EQ(6, sum_column->at(0));
//		EXPECT_EQ(12, sum_column->at(1));		
//	}	
//	
//	TEST_F(QueryTest, ProcessesQueryWithNoResults) {
//		this->LoadProductData();
//		
//		shared_ptr<Query> query(new Query(this->fragments, this->measures));
//		query->conditions->eq("store", "S3");
//		query->conditions->eq("product", "?");
//		query->conditions->eq("season", "?");
//		
//		shared_ptr<Aggregation> record_count(new COUNT("records"));
//		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
//		query->aggregations->push_back(record_count);
//		query->aggregations->push_back(sales_sum);
//		
//		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
//		
//		if(!executed.get<0>()) {
//			FAIL() << "Query execution failed: " << executed.get<1>();
//		}
//		
//		shared_ptr<Table> table = executed.get<2>();
//				
//		shared_ptr< TListColumn<string> > values_column = 
//		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
//		
//		vector<string> values;
//		ASSERT_EQ(0, values_column->size());
//
//		shared_ptr< TColumn<double> > count_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
//		
//		ASSERT_EQ(0, count_column->size());
//		
//		shared_ptr< TColumn<double> > sum_column = 
//		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
//		
//		ASSERT_EQ(0, sum_column->size());
//	}
}  // namespace
