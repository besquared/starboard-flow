/*
 *  MockIndices.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_domain_mock_indices_h_
#define _flow_testing_domain_mock_indices_h_

#include <Common.h>
#include <Domain/Indices.h>

#include <Testing/Domain/Data/MockMeta.h>

namespace Flow {
	namespace Testing {
		namespace Domain {
			class MockIndices : public ::Domain::Indices {				
			public:
				MockIndices(::Domain::Data::Meta* meta) : 
				::Domain::Indices::Indices(meta) {}
				
				MOCK_METHOD1(Insert, bool(const ::Domain::Data::Record& record));
				MOCK_METHOD2(Lookup, bool(const ValueMap& specified, ::Domain::Data::RIDList& results));
				MOCK_METHOD3(Lookup, bool(const set<string>& dimensions, const Conditions& conditions, ::Domain::Data::RIDTree& results));				
			};
		}
	}
}

#endif