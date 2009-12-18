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
#include "RecordList.h"

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
		
		bool Get(const string& key, string& result);
		bool Get(const string& key, set<string>& results);
		bool Get(const string& key, vector<string>& results);
		bool Get(const string& key, RecordList& results);
		
		bool Put(const string& key, const string& value);
		bool PutDup(const string& key, const string& value);
		bool PutDup(const string& key, const RecordID& record);
		bool PutCat(const string& key, const RecordID& record);
		
		bool Add(const string& key, const int value, int& result);
		bool Add(const string& key, const double value, double& result);
		
		string Error();
		int ErrorCode();
		
		static bool Create(const string& path, const string& name);
		static string Path(const string& path, const string& name);
	};
}

#endif