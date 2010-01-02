/*
 *  Block.h
 *  Flow
 *
 *  Created by Josh Ferguson on 1/2/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 *  A block is a representation of a two-column structure
 *   where the first column is a key and the second is a RIDList
 */

#ifndef _flow_engine_analytical_block_h_
#define _flow_engine_analytical_block_h_

#include <Common.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>

#include "Key.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;
using namespace Flow::Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Block : public vector< pair<Key, RIDList> > {
			public:
				void push_back(const vector<string>& components, const RIDList& records);
			};
		}
	}
}


#endif