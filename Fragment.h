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
				
		vector<RecordID> Lookup(const map<string, string>& values);
		map< string, vector<string> > Lookup(const set<string>& dimensions);
		map<string, RecordID> Lookup(const string& dimension, const vector<string>& values);
		
		bool Insert(RecordID record, const map<string, string>& dimensions);
	};
}

#endif