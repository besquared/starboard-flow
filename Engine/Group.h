/*
 *  Group.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

// mygroup.push_back(1);
// mygroup.push_back("amount", 100.20);
// mygroup.push_back("station", "montgomery");

// RIDList& mygroup.records();
// vector<double>& mygroup.measures("amount");
// vector<string>& mygroup.values("station")

// RecordID mygroup.record(0);
// double mygroup.measure("amount", 0);
// string& mygroup.value("station", 0);

#ifndef _flow_engine_group_h_
#define _flow_engine_group_h_

#include <Common.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>

using namespace std;
using namespace Flow::Domain;

namespace Flow {
	namespace Engine {
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
