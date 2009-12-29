/*
 *  MockMeasures.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_domain_mock_measures_h_
#define _flow_testing_domain_mock_measures_h_

#include <Common.h>
#include <Domain/Measures.h>

namespace Flow {
	namespace Testing {
		namespace Domain {
			class MockMeasures : public ::Domain::Measures {
			public:
				MockMeasures(const string& path) : 
				::Domain::Measures::Measures(path) {}
				
				MOCK_METHOD2(Insert, bool(const RecordID, const map<string, double>&));
				MOCK_METHOD3(Lookup, void(const string&, const ::Domain::Data::RIDList&, vector<double>&));
			};
		}
	}
}

#endif