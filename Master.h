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
		virtual ~Master();
		
		virtual bool Fragments(vector<string>& results);		
		virtual bool Fragment(const string& dimension, string& result);

		virtual bool Dimensions(set<string>& results);
		virtual bool Dimensions(const string& fragment, set<string>& results);
		virtual bool Dimensions(const set<string>& fragment, set<string>& results);
		
		virtual bool Allocate(const set<string>& dimensions);
		
		virtual bool GenerateRecordID(RecordID& result);
		
		static bool Create(const string& path);
		
	private:
		class Fragments {
			Master* master;
		public:
			Fragments(Master* master);
			Flow::Fragment Get();
		};		
	};
}

#endif