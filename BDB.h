/*
 *  BDB.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _bdb_included_
#define _bdb_included_

#include "Common.h"

namespace Flow {
	class BDB {
		string path;
		TCBDB *database;

	protected:
		virtual string Path() = 0;

	public:		
		BDB(const string& path);
		~BDB();
		
		tuple<bool, string> Create();
		tuple<bool, string> OpenReader();
		tuple<bool, string> OpenWriter();
		tuple<bool, string> Open(bool writer);
		tuple<bool, string> Close();
		tuple<bool, string> Truncate();
		
		bool BDB::Get(const string& key, string& result);
		bool BDB::Get(const string& key, vector<string>& results);
		bool BDB::Get(const string& key, vector<RecordID>& results);
		
		bool BDB::Put(const string& key, const string& value);
		bool BDB::Put(const string& key, const RecordID& value);
		bool BDB::Put(const string& key, const vector<string>& values);
		bool BDB::Put(const string& key, const vector<RecordID>& records);

		bool BDB::PutDup(const string& key, const string& value);
		bool BDB::PutDup(const string& key, const RecordID& record);
		
		/*
		 * Transactions
		 */
		tuple<bool, string> TransactionBegin();
		tuple<bool, string> TransactionAbort();
		tuple<bool, string> TransactionCommit();
		
		string Error();
	};
}

#endif