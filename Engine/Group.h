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

// RID mygroup.record(0);
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
		class Group : public Domain::Data::RIDList {
		protected:
			map<string, double> aggregates_;
			map< string, vector<double> > measures_;
			map< string, vector<string> > dimensions_;
			
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
				// TODO use vector member method here instead
				copy(values.begin(), values.end(), back_inserter(measures_[name]));
			}
			
			void clear_measures() {
				measures_.clear();
			}
			      
      void dimension(const string& dimension, const string& value) {
        dimensions_[dimension].push_back(value);
      }
      
			vector<string>& dimensions(const string& name) {
				return dimensions_[name];
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
