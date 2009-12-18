/*
 *  MockFragments.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/18/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _included_mock_master_
#define _included_mock_master_

#include "Common.h"
#include "Master.h"

namespace Flow {
	namespace Testing {
		namespace Database {
			class MockMaster : public Master {
			public:
				MockMaster(const string& path) : Master::Master(path) {
					cout << "Constructing MockMaster with path " << path << endl;
					cout << "MockMaster->path is now " << this->path << endl;
				}
			};
		}
	}
}

#endif