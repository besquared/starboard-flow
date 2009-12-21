/*
 *  MockIndex.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/19/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_mock_index_h_
#define _flow_mock_index_h_

#include "Common.h"
#include "Index.h"

namespace Flow {
	namespace Testing {
		namespace Database {
			class MockIndex : public Index {
			public:
				MockIndex(const string& path) : Index::Index(path) {}
				
				MOCK_METHOD0(OpenWriter, bool());
				MOCK_METHOD0(OpenReader, bool());
				MOCK_METHOD0(Close, bool());
				
				MOCK_METHOD1(Insert, bool(const map<string, string>& dimensions));
				MOCK_METHOD2(Lookup, bool(const set<string>& dimensions, ValuesMap& results));
				MOCK_METHOD3(Lookup, bool(const string& dimension, const vector<string>& values, RIDMap& results));
			};
		}
	}
}

#endif