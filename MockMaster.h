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
			class MockMaster : public Flow::Master {
			public:
				MockMaster() : Master("") {}
				MOCK_METHOD0(OpenWriter, bool());
				MOCK_METHOD0(Close, bool());
			};
		}
	}
}

#endif