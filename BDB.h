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
	public:
		string path;
		TCBDB *database;
		
		BDB(const string& path);
		~BDB();
		
		tuple<bool, string> Create();
		tuple<bool, string> OpenReader();
		tuple<bool, string> OpenWriter();
		tuple<bool, string> Open(bool writer);
		tuple<bool, string> Close();
		tuple<bool, string> Truncate();
		
		void BDB::Get(const string& key, string& result);
		void BDB::Get(const string& key, int& result);
		void BDB::Get(const string& key, double& result);
		void BDB::Get(const string& key, char* result);
		
		string Error();
		
		virtual string Path() = 0;
	};
}

#endif