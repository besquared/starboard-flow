/*
 *  QueryTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.cpp"

namespace {
	class QueryTest : public ::testing::Test {
	protected:
		TestHelper* helper;
		Measures* measures;
		ShellFragments* fragments;
		
		QueryTest() {}
		virtual ~QueryTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->measures = new Measures("/tmp/flow");
			this->fragments = new ShellFragments("/tmp/flow");
			this->fragments->database->Truncate();
			tuple<bool, string> opened = this->fragments->database->OpenWriter();
			
			if(!opened.get<0>()) {
				FAIL() << "Could not open fragments database for dimensions test";
			}
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->fragments);
		}
		
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
		virtual void LoadProductData() {
			int record_id = 1;
			map<string, string> row;
			map<string, double> measures;
			row["store"] = "S1";
			row["product"] = "P1";
			row["season"] = "s";
			measures["sales"] = 6;
			
			this->fragments->Insert(record_id, row);
			this->measures->Insert(record_id, measures);
			
			record_id = 2;
			row["store"] = "S1";
			row["product"] = "P2";
			row["season"] = "s";
			measures["sales"] = 12;
			this->fragments->Insert(record_id, row);
			this->measures->Insert(record_id, measures);
			
			record_id = 3;
			row["store"] = "S2";
			row["product"] = "P1";
			row["season"] = "f";
			measures["sales"] = 9;
			
			this->fragments->Insert(record_id, row);		
			this->measures->Insert(record_id, measures);
		}
		
		/*
		 * +----+----+----+----+----+
		 * | A  | B  | C  | D  | E  |
		 * +----|----|----|----|----+
		 * | a1 | b1 | c1 |    |    |
		 * +----|----|----|----|----+
		 * | a2 | b1 | c1 | d1 | e1 |
		 * +----+----+----+----+----+
		 * | a3 |    | c2 |    | e2 |
		 * +----+----+----+----+----+
		 *
		 */		
		virtual void LoadSparseData() {
			int record_id;
			
			record_id = 1;
			map<string, string> row;
			row["A"] = "a1";
			row["B"] = "b1";
			row["C"] = "c1";
			
			this->fragments->Insert(record_id, row);
			
			record_id = 2;
			map<string, string> row2;
			row2["A"] = "a2";
			row2["B"] = "b1";
			row2["C"] = "c1";
			row2["D"] = "d1";
			row2["E"] = "e1";
			
			this->fragments->Insert(record_id, row2);
			
			record_id = 3;
			map<string, string> row3;
			row3["A"] = "a3";
			row3["C"] = "c2";
			row3["E"] = "e2";
			
			this->fragments->Insert(record_id, row3);
		}
	};
		
	TEST_F(QueryTest, ProcessesPurePointQuery) {
		this->LoadProductData();
		
		shared_ptr<Query> query(new Query(this->fragments, this->measures));
		query->conditions->push_back("store", "S1");
		
		shared_ptr<Aggregation> record_count(new COUNT("records"));
		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
		query->aggregations->push_back(record_count);
		query->aggregations->push_back(sales_sum);
		
		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
		
		if(!executed.get<0>()) {
			FAIL() << "Query execution failed: " << executed.get<1>();
		}
		
		shared_ptr<Table> table = executed.get<2>();
		
		cout << table->Inspect() << endl;
		
		shared_ptr< TListColumn<string> > values_column = 
		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
		
		vector<string> values;
		ASSERT_EQ(1, values_column->size());
		
		values = values_column->at(0);
		ASSERT_EQ(1, values.size());
		EXPECT_EQ("S1", values[0]);
		
		shared_ptr< TColumn<double> > count_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
		
		ASSERT_EQ(1, count_column->size());
		EXPECT_EQ(2, count_column->at(0));
		
		shared_ptr< TColumn<double> > sum_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
		
		ASSERT_EQ(1, sum_column->size());
		EXPECT_EQ(18, sum_column->at(0));
	}

	TEST_F(QueryTest, ProcessesPureRangeQuery) {
		this->LoadProductData();
		
		shared_ptr<Query> query(new Query(this->fragments, this->measures));
		query->conditions->push_back("store", "?");
		
		shared_ptr<Aggregation> record_count(new COUNT("records"));
		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
		query->aggregations->push_back(record_count);
		query->aggregations->push_back(sales_sum);
		
		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
		
		if(!executed.get<0>()) {
			FAIL() << "Query execution failed: " << executed.get<1>();
		}
		
		shared_ptr<Table> table = executed.get<2>();
		
		cout << table->Inspect() << endl;
		
		shared_ptr< TListColumn<string> > values_column = 
		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
		
		vector<string> values;
		ASSERT_EQ(2, values_column->size());
		
		values = values_column->at(0);
		ASSERT_EQ(1, values.size());
		EXPECT_EQ("S1", values[0]);
		
		values = values_column->at(1);
		ASSERT_EQ(1, values.size());
		EXPECT_EQ("S2", values[0]);
		
		shared_ptr< TColumn<double> > count_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
		
		ASSERT_EQ(2, count_column->size());
		EXPECT_EQ(2, count_column->at(0));
		EXPECT_EQ(1, count_column->at(1));

		shared_ptr< TColumn<double> > sum_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
		
		ASSERT_EQ(2, sum_column->size());
		EXPECT_EQ(18, sum_column->at(0));
		EXPECT_EQ(9, sum_column->at(1));
	}

	TEST_F(QueryTest, ProcessesMixedQuery) {
		this->LoadProductData();
		
		shared_ptr<Query> query(new Query(this->fragments, this->measures));
		query->conditions->push_back("store", "S1");
		query->conditions->push_back("product", "?");
		query->conditions->push_back("season", "?");
		
		shared_ptr<Aggregation> record_count(new COUNT("records"));
		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
		query->aggregations->push_back(record_count);
		query->aggregations->push_back(sales_sum);
		
		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
		
		if(!executed.get<0>()) {
			FAIL() << "Query execution failed: " << executed.get<1>();
		}
		
		shared_ptr<Table> table = executed.get<2>();
		
		cout << table->Inspect() << endl;
		
		shared_ptr< TListColumn<string> > values_column = 
		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
		
		vector<string> values;
		ASSERT_EQ(2, values_column->size());
		
		values = values_column->at(0);
		ASSERT_EQ(3, values.size());
		EXPECT_EQ("S1", values[0]);
		EXPECT_EQ("P1", values[1]);
		EXPECT_EQ("s", values[2]);
		
		values = values_column->at(1);
		ASSERT_EQ(3, values.size());
		EXPECT_EQ("S1", values[0]);
		EXPECT_EQ("P2", values[1]);
		EXPECT_EQ("s", values[2]);
				
		shared_ptr< TColumn<double> > count_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
		
		ASSERT_EQ(2, count_column->size());
		EXPECT_EQ(1, count_column->at(0));
		EXPECT_EQ(1, count_column->at(1));
		
		shared_ptr< TColumn<double> > sum_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
		
		ASSERT_EQ(2, sum_column->size());
		EXPECT_EQ(6, sum_column->at(0));
		EXPECT_EQ(12, sum_column->at(1));		
	}	
	
	TEST_F(QueryTest, ProcessesQueryWithNoResults) {
		this->LoadProductData();
		
		shared_ptr<Query> query(new Query(this->fragments, this->measures));
		query->conditions->push_back("store", "S3");
		query->conditions->push_back("product", "?");
		query->conditions->push_back("season", "?");
		
		shared_ptr<Aggregation> record_count(new COUNT("records"));
		shared_ptr<Aggregation> sales_sum(new SUM("sales"));
		query->aggregations->push_back(record_count);
		query->aggregations->push_back(sales_sum);
		
		tuple< bool, string, shared_ptr<Table> > executed = query->Execute();
		
		if(!executed.get<0>()) {
			FAIL() << "Query execution failed: " << executed.get<1>();
		}
		
		shared_ptr<Table> table = executed.get<2>();
		
		cout << table->Inspect() << endl;
		
		shared_ptr< TListColumn<string> > values_column = 
		static_pointer_cast< TListColumn<string> >(table->columns->at("values"));
		
		vector<string> values;
		ASSERT_EQ(0, values_column->size());

		shared_ptr< TColumn<double> > count_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("count_records"));
		
		ASSERT_EQ(0, count_column->size());
		
		shared_ptr< TColumn<double> > sum_column = 
		static_pointer_cast< TColumn<double> >(table->columns->at("sum_sales"));
		
		ASSERT_EQ(0, sum_column->size());
	}
}  // namespace
