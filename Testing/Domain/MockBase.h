/*
 *  MockBase.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_domain_mock_base_h_
#define _flow_testing_domain_mock_base_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Testing/Domain/MockDimensions.h>

namespace Flow {
	namespace Testing {
		namespace Domain {
			class MockBase : public ::Domain::Base {
			public:
				MockBase(const string& path, const string& dpath) : 
				::Domain::Base::Base(path, dpath) {}
			};
		}
	}
}

#endif