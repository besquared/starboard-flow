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
#include "Domain/Data/Dimension.h"
#include "Domain/Data/Record.h"

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		class Dimensions {
		protected:
			string path;
			
		public:
			Dimensions(const string& path);
			
			bool Insert(const Record& record);
			void Lookup(const string& dimension, const RIDList& records, vector<string>& results);
		};
	}
}

#endif