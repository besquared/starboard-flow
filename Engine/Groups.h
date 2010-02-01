/*
 *  Groups.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_groups_h_
#define _flow_engine_groups_h_

#include <Common.h>

#include "Group.h"

using namespace std;

namespace Flow {
	namespace Engine {
		class Groups : public vector<Group> {
		public:
			vector<string> dimensions;
			
			Groups() : vector<Group>() {}
			
			Groups(const vector<string>& dimensions) : vector<Group>() {
				this->dimensions = dimensions;
			}
		};
	}
}

#endif