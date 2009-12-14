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
	protected:
		string path;
		string name;
		TCBDB *database;
		
	public:		
		BDB(const string& path, const string& name);
		~BDB();
		
		bool OpenReader();
		bool OpenWriter();
		bool Open(int mode);
		bool Close();
		bool Truncate();
		
		bool BDB::Get(const string& key, string& result);
		bool BDB::Get(const string& key, set<string>& results);
		bool BDB::Get(const string& key, vector<string>& results);
		bool BDB::Get(const string& key, vector<RecordID>& results);
		
		bool BDB::Put(const string& key, const string& value);
		bool BDB::Put(const string& key, const RecordID& value);
		bool BDB::PutDup(const string& key, const string& value);
		bool BDB::PutDup(const string& key, const RecordID& record);
		
		bool BDB::Add(const string& key, const int value, int& result);
		bool BDB::Add(const string& key, const double value, double& result);
		
		string Error();
		
		static bool Create(const string& path, const string& name);
		static string Path(const string& path, const string& name);
	};
}

#endif