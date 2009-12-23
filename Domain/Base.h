/*
 *  Base.h
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

#ifndef _flow_domain_base_h_
#define _flow_domain_base_h_

#include <Common.h>
#include <Domain/Data/RIDList.h>
#include <Domain/Data/RIDMap.h>
#include <Domain/Data/RIDTree.h>
#include <Domain/Data/Meta.h>
#include <Domain/Indices.h>
#include <Domain/Dimensions.h>
#include <Domain/Measures.h>

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		class Base {
		protected:
			string path;
			string dpath;
			Domain::Data::Meta* meta;

		public:			
			Domain::Indices* indices;
			Domain::Dimensions* dimensions;
			Domain::Measures* measures;
			
			Base(const string& path, const string& dpath);
		};
	}
}

#endif