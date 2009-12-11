/*
 *  Dimension.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _dimension_included_
#define _dimension_included_

#include "Common.h"

namespace Flow {
	class Dimension {
	public:
		string path;
		string name;
		TCHDB* database;
		
		Dimension(string path, string name);
		~Dimension();
		
		/*
		 * I/O Management
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
		string Get(RecordID key);
		void Get(const vector<RecordID>& keys, vector<string>& results);
		
		/*
		 * Writing
		 */
		tuple<bool, string> Put(RecordID key, string value);
		tuple<bool, string> PutAsync(RecordID key, string value);

		/*
		 * Transactions
		 */
		bool TransactionBegin();
		bool TransactionAbort();
		bool TransactionCommit();
		
		/*
		 * Error Handling
		 */
		string Error();
	};
}

#endif