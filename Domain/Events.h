/*
 *  Events.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/18/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * Represents a table of events
 *  accesses meta, indices, dimensions and measures
 */

#ifndef _flow_events_h_
#define _flow_events_h_

#include "Common.h"

#include "Meta.h"
#include "Indices.h"
#include "Dimensions.h"
#include "Measures.h"

namespace Flow {
	class Events {
	protected:
		string path;
		string dpath;
		
		Meta* meta;
		Indices* indices;
		Dimensions* dimensions;
		Measures* measures;
		
	public:
		Events(const string& path, const string& dpath);
	};
}

#endif