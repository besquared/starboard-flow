/*
 *  WorkSet.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/7/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_work_set_h_
#define _flow_engine_work_set_h_

#include <Common.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>

namespace Flow {
	namespace Engine {
    using namespace std;
    using namespace Domain::Data;
    
		class WorkSet {      
		public:
			map<string, string> values;
      
      RIDList records;
			map<string, double> aggregates;
			map< string, vector<double> > measures;
			map< string, vector<string> > dimensions;
      
			WorkSet(const map<string, string>& values) {
				this->values = values;
			}
      
      WorkSet(const map<string, string>& values, const RIDList records) {
        this->values = values;
        this->records = records;
      }
		};
	}
}

#endif
