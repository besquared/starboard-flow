/*
 *  Group.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_group_h_
#define _flow_engine_group_h_

#include <Common.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>

namespace Flow {
	namespace Engine {
    using namespace std;

		class Group {
    public:
			vector<string> values;
      Domain::Data::RIDList records;
			map<string, double> aggregates;
			map< string, vector<double> > measures;
			map< string, vector<string> > dimensions;
      
			Group(const vector<string>& values) {
				this->values = values;
			}
		};
	}
}

#endif
