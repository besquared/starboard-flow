/*
 *  MockDimensions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_domain_mock_dimensions_h_
#define _flow_testing_domain_mock_dimensions_h_

#include <Common.h>
#include <Domain/Dimensions.h>

namespace Flow {
	namespace Testing {
		namespace Domain {
			class MockDimensions : public ::Domain::Dimensions {
			public:
				MockDimensions(const string& path) : 
				::Domain::Dimensions::Dimensions(path) {}
			};
		}
	}
}

#endif