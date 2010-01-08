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
#include <Domain/Data/RIDList.h>

using namespace std;
using namespace Flow;
using namespace Flow::Domain;

namespace Flow {
	namespace Engine {
		class Group : public Domain::Data::RIDList {
		protected:
			map<string, double> aggregates_;
			map< string, vector<double> > measures_;
			
		public:
			vector<string> values;

			Group(const vector<string>& values) : Domain::Data::RIDList() {
				this->values = values;
			}
			
			vector<double>& measures(const string& name) {
				return measures_[name];
			}
			
			void push_measure(const string& name, const double& value) {
				measures_[name].push_back(value);
			}
			
			void push_measures(const string& name, const vector<double>& values) {
				copy(values.begin(), values.end(), back_inserter(measures_[name]));
			}
			
			double& aggregate(const string& name) {
				return aggregates_[name];
			}
			
			void aggregate(const string& name, const double& value) {
				aggregates_[name] = value;
			}
		};
	}
}

#endif
