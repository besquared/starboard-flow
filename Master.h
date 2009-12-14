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
#include "BDB.h"

namespace Flow {
	class Master : public BDB {
	public:
		string path;
		TCBDB *database;
		
		Master(const string& path);
		~Master();

		string Path();
		
		vector<string> Fragments();		
		vector<string> Fragment(const string& dimension);

		vector<string> Dimensions();
		vector<string> Dimensions(const string& fragment);
		vector<string> Dimensions(const set<string>& fragment);
		
		tuple<bool, string> Allocate(const set<string>& dimensions);
		
		tuple<bool, string, RecordID> GenerateRecordID();
	};
}

#endif