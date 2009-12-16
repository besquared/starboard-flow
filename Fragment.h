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

#include "BDB.h"

namespace Flow {
	class Fragment : public BDB {
	public:		
		Fragment(const string& path, const string& path);		
		
		bool Lookup(const map<string, string>& dimensions, vector<RecordID>& results);
		bool Lookup(const set<string>& dimensions, map< string, vector<string> >& results);
		bool Lookup(const string& dimension, const vector<string>& values, map< string, vector<RecordID> >& results);
		
		bool Insert(const map<string, string>& dimensions);
		bool Insert(const RecordID record, const map<string, string>& dimensions);

		string Key(const string& component);
		string Key(const vector<string>& components);
		string ValuesKey(const string& dimension);
		string ValueKey(const string& dimension, const string& value);
		string Component(const string& dimension, const string& value);
	};
}

#endif