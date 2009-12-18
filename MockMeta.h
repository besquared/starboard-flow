/*
 *  MockFragments.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/18/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _included_mock_meta_
#define _included_mock_meta_

#include "Common.h"
#include "Meta.h"

namespace Flow {
	namespace Testing {
		namespace Database {
			class MockMeta : public Meta {
			public:
				MockMeta(const string& path) : Meta::Meta(path) {}
				
				MOCK_METHOD0(OpenWriter, bool());
				MOCK_METHOD0(OpenReader, bool());
				MOCK_METHOD0(Close, bool());
				
				MOCK_METHOD1(Allocate, bool(const set<string>& dimensions));
				MOCK_METHOD2(Fragment, bool(const string& dimension, string& result));
			};
		}
	}
}

#endif