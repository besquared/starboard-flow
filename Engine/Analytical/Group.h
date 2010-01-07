/*
 *  Group.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_analytical_group_h_
#define _flow_engine_analytical_group_h_

#include <Common.h>
#include <Domain/Data/Record.h>

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Group : public vector<RecordID> {
			public:
				vector<string> values;
				map<string, double> aggregates;
				map< string, vector<double> > measures;
				
				Group(const vector<string>& values) : vector<RecordID>() {
					this->values = values;
				}
			};
		}
	}
}

#endif
