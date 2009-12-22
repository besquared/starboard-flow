/*
 *  ShellFragmentsTest.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TestHelper.h"

namespace {
	class ShellFragmentsTest : public ::testing::Test {
	protected:
		TestHelper *helper;
		ShellFragments *fragments;
		
		ShellFragmentsTest() {}
		virtual ~ShellFragmentsTest() {}
		
		virtual void SetUp() {
			this->helper = new TestHelper();
			this->fragments = new ShellFragments("/tmp/flow");
			this->fragments->database->Truncate();
			
			// special for this test
			Response opened = this->fragments->OpenWriter();
			
			if(!opened.get<0>()) {
				FAIL() << "Could not open fragment database for writing" << endl;
			}
		}
		
		virtual void TearDown() {
			delete(this->helper);
			delete(this->fragments);
		}
	};
	
	TEST_F(ShellFragmentsTest, ListsFragments) {		
		tuple<bool, string, int> created1 = this->fragments->Create();
		tuple<bool, string, int> created2 = this->fragments->Create();
		
		ASSERT_EQ(ok, created1.get<0>());
		ASSERT_EQ(ok, created2.get<0>());
		
		vector<string> fraglist = this->fragments->List();
		ASSERT_EQ(2, fraglist.size());
		EXPECT_EQ("1", fraglist[0]);
		EXPECT_EQ("2", fraglist[1]);
	}
		
	TEST_F(ShellFragmentsTest, CreatesFragments) {
		tuple<bool, string, int> created = this->fragments->Create();
		ASSERT_EQ(ok, created.get<0>());
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		int last_fragment_id = this->fragments->database->GetInt("last_fragment_id");
		ASSERT_EQ(1, last_fragment_id);
				
		created = this->fragments->Create();
		ASSERT_EQ(ok, created.get<0>());
		
		fragments = this->fragments->List();
		ASSERT_EQ(2, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		EXPECT_EQ("2", fragments[1]);
		
		last_fragment_id = this->fragments->database->GetInt("last_fragment_id");
		ASSERT_EQ(2, last_fragment_id);
	}
	
	TEST_F(ShellFragmentsTest, PreAllocatesFragmentsAndDimensions) {
		vector<string> dimensions;
		dimensions.push_back("A");
		dimensions.push_back("B");
		dimensions.push_back("C");
		
		tuple<bool, string> allocated = this->fragments->PreAllocate(dimensions);
		ASSERT_EQ(true, allocated.get<0>());

		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		dimensions.push_back("D");
		dimensions.push_back("E");
		
		allocated = this->fragments->PreAllocate(dimensions);
		ASSERT_EQ(true, allocated.get<0>());
		
		// Do we create the proper fragments?
		fragments = this->fragments->List();
		ASSERT_EQ(2, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		EXPECT_EQ("2", fragments[1]);
		
		// Is our overall dimensions list populated correctly?
		vector<string> alldims = this->fragments->dimensions->List();
		ASSERT_EQ(5, alldims.size());
		EXPECT_EQ("A", alldims[0]);
		EXPECT_EQ("B", alldims[1]);
		EXPECT_EQ("C", alldims[2]);
		EXPECT_EQ("D", alldims[3]);
		EXPECT_EQ("E", alldims[4]);
		
		// Are each of our fragment dimension lists populated correctly?
		for(size_t i = 0; i < fragments.size(); i++) {
			vector<string> dims = this->fragments->dimensions->List(fragments[i]);
			
			if(fragments[i] == "1") {
				ASSERT_EQ(4, dims.size());
				EXPECT_EQ("A", dims[0]);
				EXPECT_EQ("B", dims[1]);
				EXPECT_EQ("C", dims[2]);
				EXPECT_EQ("D", dims[3]);
			} else if(fragments[i] == "2") {
				ASSERT_EQ(1, dims.size());
				EXPECT_EQ("E", dims[0]);
			}
		}
	}
	
	TEST_F(ShellFragmentsTest, InsertsRow) {
		int record_id = 1;
		map<string, string> row;
		row["A"] = "a1";
		row["B"] = "b1";
		row["C"] = "c1";
		
		tuple<bool, string> inserted = this->fragments->Insert(record_id, row);
		
		ASSERT_EQ(true, inserted.get<0>());
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		record_id = 2;
		row["A"] = "a2";
		row["D"] = "d1";
		row["E"] = "e1";
		
		this->fragments->Insert(record_id, row);
		
		// Do we create the proper fragments?
		fragments = this->fragments->List();
		ASSERT_EQ(2, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		EXPECT_EQ("2", fragments[1]);
		
		// Is our overall dimensions list populated correctly?
		vector<string> alldims = this->fragments->dimensions->List();
		ASSERT_EQ(5, alldims.size());
		EXPECT_EQ("A", alldims[0]);
		EXPECT_EQ("B", alldims[1]);
		EXPECT_EQ("C", alldims[2]);
		EXPECT_EQ("D", alldims[3]);
		EXPECT_EQ("E", alldims[4]);
		
		// Are each of our fragment dimension lists populated correctly?
		for(size_t i = 0; i < fragments.size(); i++) {
			vector<string> dims = this->fragments->dimensions->List(fragments[i]);
			
			if(fragments[i] == "1") {
				ASSERT_EQ(4, dims.size());
				EXPECT_EQ("A", dims[0]);
				EXPECT_EQ("B", dims[1]);
				EXPECT_EQ("C", dims[2]);
				EXPECT_EQ("D", dims[3]);
			} else if(fragments[i] == "2") {
				ASSERT_EQ(1, dims.size());
				EXPECT_EQ("E", dims[0]);
			}
		}
		
		// Do each of our dimensions have the correct set values?
		for(int j = 0; j < alldims.size(); j++) {
			vector<string> values = this->fragments->dimensions->Values(alldims[j]);
						
			if(alldims[j] == "A") {
				ASSERT_EQ(2, values.size());
				EXPECT_EQ("a1", values[0]);
				EXPECT_EQ("a2", values[1]);
			} else if(alldims[j] == "B") {
				ASSERT_EQ(1, values.size());
				EXPECT_EQ("b1", values[0]);
			} else if(alldims[j] == "C") {
				ASSERT_EQ(1, values.size());
				EXPECT_EQ("c1", values[0]);
			} else if(alldims[j] == "D") {
				ASSERT_EQ(1, values.size());
				EXPECT_EQ("d1", values[0]);
			} else if (alldims[j] == "E") {
				ASSERT_EQ(1, values.size());
				EXPECT_EQ("e1", values[0]);
			}
		}
		
		// Do we have the correct indexing keys and record id lists?
		//  How do we test this? Do we do lookups? I think probably
		Inquired inquired;
		this->fragments->Lookup(alldims, inquired);
		
		Inquired::iterator outter;
		for(outter = inquired.begin(); outter != inquired.end(); outter++) {
			InquiredDimension::iterator inner;
			InquiredDimension dimension = outter->second;			
			for(inner = dimension.begin(); inner != dimension.end(); inner++) {
				if(outter->first == "A") {
					if(inner->first == "a1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
					} else if(inner->first == "a2") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(2, inner->second[0]);
					}
				} else if(outter->first == "B") {
					if(inner->first == "b1") {
						ASSERT_EQ(2, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
						EXPECT_EQ(2, inner->second[1]);
					}
				} else if(outter->first == "C") {
					if(inner->first == "c1") {
						ASSERT_EQ(2, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
						EXPECT_EQ(2, inner->second[1]);						
					}
				} else if(outter->first == "D") {
					if(inner->first == "d1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(2, inner->second[0]);
					}
				} else if(outter->first == "E") {
					if(inner->first == "e1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(2, inner->second[0]);
					}
				}				
			}
		}
	}

	TEST_F(ShellFragmentsTest, InquiresRecordIds) {
		int record_id = 1;
		map<string, string> row;
		row["A"] = "a1";
		row["B"] = "b1";
		row["C"] = "c1";
		
		this->fragments->Insert(record_id, row);
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		record_id = 2;
		row["A"] = "a2";
		row["D"] = "d1";
		row["E"] = "e1";
		
		this->fragments->Insert(record_id, row);
		
		vector<string> dimensions;
		dimensions.push_back("B");
		
		// {B => ?}
		Inquired inquired;
		this->fragments->Lookup(dimensions, inquired);
		
		Inquired::iterator outter;
		for(outter = inquired.begin(); outter != inquired.end(); outter++) {
			InquiredDimension::iterator inner;
			InquiredDimension dimension = outter->second;			
			for(inner = dimension.begin(); inner != dimension.end(); inner++) {
				if(outter->first == "B") {
					if(inner->first == "b1") {
						ASSERT_EQ(2, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
						EXPECT_EQ(2, inner->second[1]);
					}
				} else {
					FAIL() << "Inquired contained an unexpected dimension";
				}
			}
		}		
	}
	
	TEST_F(ShellFragmentsTest, InstantiatesRecordIds) {
		int record_id = 1;
		map<string, string> row;
		row["A"] = "a1";
		row["B"] = "b1";
		row["C"] = "c1";
		
		this->fragments->Insert(record_id, row);
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		record_id = 2;
		row["A"] = "a2";
		row["D"] = "d1";
		row["E"] = "e1";
		
		this->fragments->Insert(record_id, row);
		
		map<string, string> conditions;
		conditions["A"] = "a1";
		
		Instantiated instantiated;
		this->fragments->Lookup(conditions, instantiated);
		
		ASSERT_EQ(1, instantiated.size());
		EXPECT_EQ(1, instantiated[0]);
	}
	
	TEST_F(ShellFragmentsTest, InstantiatesAndIntersectRecordIds) {
		int record_id = 1;
		map<string, string> row;
		row["A"] = "a1";
		row["B"] = "b1";
		row["C"] = "c1";
		
		this->fragments->Insert(record_id, row);
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		record_id = 2;
		row["A"] = "a2";
		row["D"] = "d1";
		row["E"] = "e1";
		
		this->fragments->Insert(record_id, row);
		
		map<string, string> conditions;
		conditions["A"] = "a1";
		
		vector<string> dimensions;
		dimensions.push_back("B");
		
		// {A => a1, B => ?}
		Inquired inquired;
		this->fragments->Lookup(conditions, dimensions, inquired);
				
		Inquired::iterator outter;
		for(outter = inquired.begin(); outter != inquired.end(); outter++) {
			InquiredDimension::iterator inner;
			InquiredDimension dimension = outter->second;			
			for(inner = dimension.begin(); inner != dimension.end(); inner++) {
				if(outter->first == "A") {
					if(inner->first == "a1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
					}
				} else if(outter->first == "B") {
					if(inner->first == "b1") {
						ASSERT_EQ(2, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
						EXPECT_EQ(2, inner->second[1]);
					}
				} else {
					FAIL() << "Inquired contained unexpected dimension";
				}
			}
		}		
	}
	
	TEST_F(ShellFragmentsTest, InstantiatesRecordIdsWithNoConditions) {
		int record_id = 1;
		map<string, string> row;
		row["A"] = "a1";
		row["B"] = "b1";
		row["C"] = "c1";
		
		this->fragments->Insert(record_id, row);
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		record_id = 2;
		row["A"] = "a2";
		row["D"] = "d1";
		row["E"] = "e1";
		
		this->fragments->Insert(record_id, row);
		map<string, string> conditions;
		
		vector<string> dimensions;
		dimensions.push_back("A");
		dimensions.push_back("B");
		
		Inquired inquired;
		this->fragments->Lookup(conditions, dimensions, inquired);
		
		Inquired::iterator outter;
		for(outter = inquired.begin(); outter != inquired.end(); outter++) {
			InquiredDimension::iterator inner;
			InquiredDimension dimension = outter->second;			
			for(inner = dimension.begin(); inner != dimension.end(); inner++) {
				if(outter->first == "A") {
					if(inner->first == "a1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
					} else if(inner->first == "a2") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(2, inner->second[0]);
					}
				} else if(outter->first == "B") {
					if(inner->first == "b1") {
						ASSERT_EQ(2, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
						EXPECT_EQ(2, inner->second[1]);
					}
				} else {
					FAIL() << "Inquired contained unexpected dimension";
				}
			}
		}				
	}

	TEST_F(ShellFragmentsTest, InstantiatesRecordIdsWithNoInquired) {
		int record_id = 1;
		map<string, string> row;
		row["A"] = "a1";
		row["B"] = "b1";
		row["C"] = "c1";
		
		this->fragments->Insert(record_id, row);
		
		vector<string> fragments = this->fragments->List();
		ASSERT_EQ(1, fragments.size());
		EXPECT_EQ("1", fragments[0]);
		
		record_id = 2;
		row["A"] = "a2";
		row["D"] = "d1";
		row["E"] = "e1";
		
		this->fragments->Insert(record_id, row);
		map<string, string> conditions;
		conditions["A"] = "a1";
		conditions["B"] = "b1";
		
		vector<string> dimensions;
		
		Inquired inquired;
		this->fragments->Lookup(conditions, dimensions, inquired);
		
		Inquired::iterator outter;
		for(outter = inquired.begin(); outter != inquired.end(); outter++) {
			InquiredDimension::iterator inner;
			InquiredDimension dimension = outter->second;			
			for(inner = dimension.begin(); inner != dimension.end(); inner++) {
				if(outter->first == "A") {
					if(inner->first == "a1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
					} else {
						FAIL() << "Unexpected value for dimension A";
					}
				} else if(outter->first == "B") {
					if(inner->first == "b1") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
					} else {
						FAIL() << "Unexpected value for dimension B";
					}
				} else {
					FAIL() << "Inquired contained unexpected dimension";
				}
			}
		}
	}

	TEST_F(ShellFragmentsTest, LooksUpRecordsWithFilters) {
		int record_id;
		map<string, string> row;

		record_id = 1;
		row["store"] = "S1";
		row["product"] = "P1";
		row["season"] = "s";
		row["day"] = "09";
		row["month"] = "12";
		row["year"] = "2009";
		
		this->fragments->Insert(record_id, row);
		
		record_id = 2;
		row["store"] = "S1";
		row["product"] = "P2";
		row["season"] = "s";
		row["day"] = "09";
		row["month"] = "12";
		row["year"] = "2008";
		
		this->fragments->Insert(record_id, row);
		
		map<string, string> instantiate;
		instantiate["store"] = "S1";
		
		vector<string> inquire;
		inquire.push_back("year");

		Conditions conditions;
		conditions.gt("year", "2008");

		Inquired results;
		this->fragments->Lookup(instantiate, inquire, conditions, results);
		
		Inquired::iterator outter;
		for(outter = results.begin(); outter != results.end(); outter++) {
			InquiredDimension::iterator inner;
			InquiredDimension dimension = outter->second;			
			for(inner = dimension.begin(); inner != dimension.end(); inner++) {
				if(outter->first == "store") {
					if(inner->first == "S1") {
						ASSERT_EQ(2, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
						EXPECT_EQ(2, inner->second[1]);
					} else {
						FAIL() << "Unexpected value for dimension store";
					}
				} else if(outter->first == "year") {
					if(inner->first == "2009") {
						ASSERT_EQ(1, inner->second.size());
						EXPECT_EQ(1, inner->second[0]);
					} else {
						FAIL() << "Unexpected value for dimension year";
					}
				} else {
					FAIL() << "Unexpected dimension";
				}
			}
		}		
	}	
}  // namespace

