/*
 *  Dimensions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _dimensions_included_
#define _dimensions_included_

#include "Common.h"
#include "Dimension.h"

namespace Flow {
	class Dimensions {
	public:
		string path;
		
		Dimensions(const string& path);
		
		tuple< bool, string, shared_ptr<Dimension> > Create(const string& name);
		tuple< bool, string, shared_ptr<Dimension> > OpenReader(const string& name);
		tuple< bool, string, shared_ptr<Dimension> > OpenWriter(const string& name);
		
		tuple<bool, string> Insert(RecordID record, const map<string, string>& dimensions);
	};
}

#endif