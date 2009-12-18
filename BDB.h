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
		virtual ~BDB();
		
		virtual bool OpenReader();
		virtual bool OpenWriter();
		virtual bool Open(int mode);
		virtual bool Close();
		virtual bool Truncate();
		
		virtual bool Get(const string& key, string& result);
		virtual bool Get(const string& key, set<string>& results);
		virtual bool Get(const string& key, vector<string>& results);
		virtual bool Get(const string& key, RecordList& results);
		
		virtual bool Put(const string& key, const string& value);
		virtual bool PutDup(const string& key, const string& value);
		virtual bool PutCat(const string& key, const RecordID& record);
		
		virtual bool Add(const string& key, const int value, int& result);
		virtual bool Add(const string& key, const double value, double& result);
		
		virtual string Error();
		virtual int ErrorCode();
		
		static bool Create(const string& path, const string& name);
		static string Path(const string& path, const string& name);
	};
}

#endif