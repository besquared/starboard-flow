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

#include <Testing/Domain/Data/MockMeta.h>
#include <Testing/Domain/MockIndices.h>
#include <Testing/Domain/MockDimensions.h>
#include <Testing/Domain/MockMeasures.h>

namespace Flow {
	namespace Testing {
		namespace Domain {
			class MockBase : public ::Domain::Base {
			protected:
				string path;
				string dpath;
				Data::MockMeta* meta;
				
			public:
				Domain::MockIndices* indices;
				Domain::MockDimensions* dimensions;
				Domain::MockMeasures* measures;

				MockBase(const string& path, const string& dpath) {
					this->path = path;
					this->dpath = dpath;
					this->meta = new Domain::Data::MockMeta(this->path);
					this->indices = new Domain::MockIndices(this->meta);
					this->dimensions = new Domain::MockDimensions(this->dpath);
					this->measures = new Domain::MockMeasures(this->dpath);
				}
			};
		}
	}
}

#endif