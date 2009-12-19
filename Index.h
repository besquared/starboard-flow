/*
 *  Index.h
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
	class Index : public BDB {
	public:		
		Index(const string& path);		
		
		static bool Create(const string& path);
		
		/*
		 * Returns a list of records corresponding to the specified dimension values
		 */
		virtual bool Lookup(const map<string, string>& dimensions, RecordList& results);
		
		/*
		 * Returns a set of values for each given dimension as a map
		 */
		virtual bool Lookup(const set<string>& dimensions, map< string, vector<string> >& results);
		
		/*
		 * Returns record lists for the given dimension for each given value
		 */
		virtual bool Lookup(const string& dimension, const vector<string>& values, RecordMap& results);
		
		/*
		 * Uniquely inserts a set of dimensions and their values
		 */
		virtual bool Insert(const map<string, string>& dimensions);
		
		/*
		 * Inserts a single row into the index
		 */
		virtual bool Insert(const RecordID record, const map<string, string>& dimensions);

		string Key(const string& component);
		string Key(const vector<string>& components);
		string ValuesKey(const string& dimension);
		string ValueKey(const string& dimension, const string& value);
		string Component(const string& dimension, const string& value);
	};
}

#endif