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
#include "Index.h"
#include "Indices.h"
#include "Measure.h"
#include "Measures.h"
#include "Dimension.h"
#include "Dimensions.h"

namespace Flow {
	class Base {
	public:
		string path;
		Meta* meta;
		Indices* indices;
		Measures* measures;
		Dimensions* dimensions;
		
		Base(const string& path);
		~Base();
		
		bool Insert(const Record& record, const map<string, double>& measures);
	};
}

#endif