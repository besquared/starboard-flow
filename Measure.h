/*
 *  Measure.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _measure_included_
#define _measure_included_

#include "Common.h"

namespace Flow {
	class Measure {
	public:
		string path;
		string name;
		TCFDB* database;
		
		Measure(string path, string name);
		~Measure();

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
		double Get(RecordID key);
		void Get(const vector<RecordID>& keys, vector<double>& results);
		
		/*
		 * Writing
		 */
		tuple<bool, string> Put(RecordID key, double value);
		
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