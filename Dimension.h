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
#include "RIDList.h"

namespace Flow {
	class Dimension {
	public:
		string path;
		string name;
		TCHDB* database;
		
		Dimension(const string& path, const string& name);
		~Dimension();
		string Path();

		/*
		 * I/O Management
		 */
		bool Create();
		bool Truncate();
		bool Close();
		bool Optimize();
		bool OpenReader();
		bool OpenWriter();
		bool Open(int mode);
		
		/*
		 * Reading
		 */
		void Lookup(const RecordID key, string& result);
		void Lookup(const RIDList& keys, vector<string>& results);
		void Lookup(const RIDList& keys, map<RecordID, string>& results);

		/*
		 * Writing
		 */
		bool Insert(const RecordID key, const string& value);
		
		/*
		 * Error Handling
		 */
		string Error();
	};
}

#endif