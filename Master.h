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
#include "Fragment.h"

namespace Flow {
	class Master : public BDB {
	private:
		class Fragments;
		
	public:		
		Fragments* fragments;		

		Master(const string& path);
		~Master();
		
		bool Fragments(vector<string>& results);		
		bool Fragment(const string& dimension, string& result);

		bool Dimensions(set<string>& results);
		bool Dimensions(const string& fragment, set<string>& results);
		bool Dimensions(const set<string>& fragment, set<string>& results);
		
		bool Allocate(const set<string>& dimensions);
		
		bool GenerateRecordID(RecordID& result);
		
		static bool Create(const string& path);
		
	private:
		class Fragments {
			Master* master;
		public:
			Fragments(Master* master);
			Flow::Fragment Get(const string& name);
		};		
	};
}

#endif