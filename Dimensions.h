/*
 *  Dimensions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_dimensions_h_
#define _flow_dimensions_h_

#include "Common.h"
#include "Dimension.h"
#include "Record.h"

namespace Flow {
	class Dimensions {
	protected:
		string path;
		
	public:
		Dimensions(const string& path);		
		bool Insert(const Record& record);
		bool Lookup(const string& dimension, const RIDList& keys, vector<string>& results);
	};
}

#endif