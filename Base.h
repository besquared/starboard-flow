/*
 *  Base.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * Like a database
 */

#ifndef _flow_base_h_
#define _flow_base_h_

#include "Common.h"

#include "Table.h"
#include "Dimension.h"
#include "Dimensions.h"
#include "Measure.h"
#include "Measures.h"
#include "ShellFragment.h"
#include "ShellFragments.h"

namespace Flow {
	class Base {
	public:
		string path;
		Dimensions* dimensions;
		Measures* measures;
		ShellFragments* fragments;
		
		Base(const string& path);
		~Base();
		
		tuple<bool, string> Insert(RecordID record, const map<string, string>& row, const map<string, double>& measures);
		tuple< bool, string, shared_ptr<Table> > Query(const map<string, string>& conditions);
	};
}

#endif