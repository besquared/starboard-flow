/*
 *  MockFragments.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/18/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_domain_data_mock_meta_h_
#define _flow_testing_domain_data_mock_meta_h_

#include "Common.h"
#include <Domain/Data/Meta.h>
#include <Testing/Domain/Data/MockIndex.h>

namespace Flow {
	namespace Testing {
		namespace Domain {
			namespace Data {
				class MockMeta : public Meta {
				public:
					MockMeta(const string& path) : Meta::Meta(path) {
						this->index = new MockIndex(this->path);
					}
					
					MOCK_METHOD0(OpenWriter, bool());
					MOCK_METHOD0(OpenReader, bool());
					MOCK_METHOD0(Close, bool());
					
					MOCK_METHOD1(Allocate, bool(const set<string>& dimensions));
					MOCK_METHOD2(Index, bool(const string& dimension, string& result));
				};
			}
		}
	}
}

#endif