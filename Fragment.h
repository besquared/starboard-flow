/*
 *  Fragment.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _fragment_included_
#define _fragment_included_

#include "Common.h"

namespace Flow {
	class Fragment {
	public:
		string path;
		TCBDB *database;
		bool opened;
		bool writer;
		
		Fragment(const string& path);		
		~Fragment();
		
		/*
		 * File Management
		 */
		tuple<bool, string> Create();
		tuple<bool, string> OpenReader();
		tuple<bool, string> OpenWriter();
		tuple<bool, string> Open(bool writer);
		tuple<bool, string> Close();
		tuple<bool, string> Truncate();
		string Path();
		
		/*
		 * Reading
		 */
		
		string Get(const string& key);
		int GetInt(const string& key);
		double GetDouble(const string& key);
		char * GetRaw(const string& key);
		vector<string> GetList(const string& key);
		TCLIST * GetListRaw(const string& key);
		
		vector<RecordID> GetRecords(const string& key);
		vector<RecordID> GetRecords(const vector<string>& keys);
		
		/*
		 * Writing
		 */
		
		tuple<bool, string> Put(const string& key, const string& value);
		tuple<bool, string> PutDup(const string& key, const string& value);
		tuple<bool, string> PutList(const string& key, const vector<string>& values);
		tuple<bool, string> PutRecord(const string& key, const RecordID value);
		
		tuple<bool, string, int> AddInt(const string& key, const int value);
		tuple<bool, string, double> AddDouble(const string& key, const double value);
		
		/*
		 * ShellDimensions
		 */
				
		/*
		 * Transactions
		 */
		tuple<bool, string> TransactionBegin();
		tuple<bool, string> TransactionAbort();
		tuple<bool, string> TransactionCommit();
		
		/*
		 * Keys
		 */
		vector<string> Keys();
		vector<string> Keys(const string& prefix);
		vector<string> Keys(const string& prefix, int max);
		
		/*
		 * Errors
		 */
		string Error();
		
		/*
		 * Data Conversion
		 */
		
		string Intern(char* element);
		int Fragment::InternInt(char *element);
		double Fragment::InternDouble(char *element);
		vector<string> InternList(TCLIST *list);
		vector<RecordID> InternRecords(TCLIST *list);
		
		/*
		 * Intersection
		 */
		
		TCLIST* IntersectRecords(TCLIST* a, TCLIST* b);
	};
}

#endif