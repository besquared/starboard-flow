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
	public:
		string path;
		
		Measures(const string& path);
		
		tuple< bool, string, shared_ptr<Measure> > Create(const string& name);
		tuple< bool, string, shared_ptr<Measure> > OpenReader(const string& name);
		tuple< bool, string, shared_ptr<Measure> > OpenWriter(const string& name);
		
		tuple<bool, string> Insert(RecordID record, const map<string, double>& measures);
	};
}

#endif