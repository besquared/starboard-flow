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
		
		vector<RecordID> Lookup(const map<string, string>& values);
		map< string, vector<string> > Lookup(const set<string>& dimensions);
		map<string, RecordID> Lookup(const string& dimension, const vector<string>& values);
		
		tuple<bool, string> Insert(RecordID record, const map<string, string>& dimensions);

		string Error();
	};
}

#endif