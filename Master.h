/*
 *  Master.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/13/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _master_included_
#define _master_included_

#include "Common.h"

namespace Flow {
	class Master {
	public:
		string path;
		TCBDB *database;
		
		Master(const string& path);
		~Master();

		tuple<bool, string> Create();
		tuple<bool, string> OpenReader();
		tuple<bool, string> OpenWriter();
		tuple<bool, string> Open(bool writer);
		tuple<bool, string> Close();
		tuple<bool, string> Truncate();
		string Path();
		
		double EventCount();
		vector<string> Fragments();
		vector<string> Dimensions(const string& fragment);
		vector<string> Fragment(const string& dimension);
		
		tuple<bool, string> Allocate(const set<string>& dimensions);
		
		tuple<bool, string, RecordID> GenerateRecordID();

		/*
		 * Errors
		 */
		string Error();
	};
}

#endif