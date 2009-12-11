#include "TestHelper.cpp"

namespace {
	class ShellFragmentTest : public ::testing::Test {
	 protected:
		ShellFragment *database;

		ShellFragmentTest() {}

		virtual ~ShellFragmentTest() {}

		virtual void SetUp() {
			this->database = new ShellFragment("/tmp/flow");
			this->database->Truncate();
			this->database->OpenWriter();
		}

		virtual void TearDown() {
			delete(this->database);
		}
	};
	
	TEST_F(ShellFragmentTest, TruncatesDatabase) {
		this->database->Put("mykey", "value");
		
		ASSERT_EQ("value", this->database->Get("mykey"));
		
		this->database->Close();
		this->database->Truncate();
		this->database->OpenWriter();
		ASSERT_EQ("", this->database->Get("mykey"));
	}
	
	TEST_F(ShellFragmentTest, PutsAndGetsKey) {
		tuple<bool, string> written = this->database->Put("mycrazykey", "mycrazyvalue");
		EXPECT_EQ(true, written.get<0>());
		EXPECT_EQ("mycrazyvalue", this->database->Get("mycrazykey"));
	}
	
	TEST_F(ShellFragmentTest, PutsAndGetsLists) {
		vector<string> elements;
		elements.push_back("element1");
		elements.push_back("element2");
		
		tuple<bool, string> written = this->database->PutList("mylist", elements);
		EXPECT_EQ(true, written.get<0>());
		
		vector<string> mylist = this->database->GetList("mylist");
		ASSERT_EQ(2, mylist.size());
		EXPECT_EQ("element1", elements[0]);
		EXPECT_EQ("element2", elements[1]);
	}
	
	TEST_F(ShellFragmentTest, GetsRecordIdLists) {
		this->database->PutRecordID("list1", 1);
		this->database->PutRecordID("list1", 2);
		this->database->PutRecordID("list1", 3);
		this->database->PutRecordID("list2", 2);
		this->database->PutRecordID("list2", 3);
		this->database->PutRecordID("list2", 4);
				
		vector<string> lists;
		lists.push_back("list1");
		lists.push_back("list2");
		
		vector<RecordID> intersection = this->database->GetRecordIdList(lists);
		ASSERT_EQ(2, intersection.size());
		EXPECT_EQ(2, intersection[0]);
		EXPECT_EQ(3, intersection[1]);
	}
	
	TEST_F(ShellFragmentTest, GetsEmptyRecordIdList) {
		this->database->PutRecordID("list1", 1);
		this->database->PutRecordID("list1", 2);
		this->database->PutRecordID("list1", 3);
		
		vector<string> lists;
		lists.push_back("list1");
		lists.push_back("list2");
		
		vector<RecordID> intersection = this->database->GetRecordIdList(lists);
		ASSERT_EQ(0, intersection.size());
	}
	
	TEST_F(ShellFragmentTest, ListsKeys) {
		this->database->Put("mykey", "myvalue");
		this->database->Put("mykey2", "myvalue");
		this->database->Put("otherkey3", "myothervalue");
		
		EXPECT_EQ(3, this->database->Keys().size());
		EXPECT_EQ(2, this->database->Keys("my").size());
		EXPECT_EQ(1, this->database->Keys("my", 1).size());
	}
	
	TEST_F(ShellFragmentTest, PerformsTransactions) {
		ASSERT_EQ(true, this->database->TransactionBegin().get<0>());
		ASSERT_EQ(true, this->database->Put("mykey", "myvalue").get<0>());
		ASSERT_EQ(true, this->database->Put("mykey2", "myvalue").get<0>());
		ASSERT_EQ(true, this->database->TransactionAbort().get<0>());
		ASSERT_EQ("", this->database->Get("mykey"));
		ASSERT_EQ("", this->database->Get("mykey2"));
		
		ASSERT_EQ(true, this->database->TransactionBegin().get<0>());
		ASSERT_EQ(true, this->database->Put("mykey", "myvalue").get<0>());
		ASSERT_EQ(true, this->database->TransactionCommit().get<0>());
		ASSERT_EQ("myvalue", this->database->Get("mykey"));		
	}
}  // namespace
