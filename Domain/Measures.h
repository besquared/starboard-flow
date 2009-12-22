/*
 *  Measures.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _measures_included_
#define _measures_included_

#include "Common.h"
#include "Measure.h"

namespace Flow {
	class Measures {
	protected:
		string path;

	public:		
		Measures(const string& path);
		
		bool Insert(RecordID record, const map<string, double>& measures);
		void Lookup(const string& measure, const RIDList& records, vector<double>& results);
	};
}

#endif