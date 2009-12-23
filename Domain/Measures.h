/*
 *  Measures.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_measures_h_
#define _flow_domain_measures_h_

#include <Common.h>
#include "Domain/Data/Measure.h"

using namespace std;
using namespace Flow;
namespace Data = Flow::Domain::Data;

namespace Flow {
	namespace Domain {
		class Measures {
		protected:
			string path;

		public:		
			Measures(const string& path);
			
			bool Insert(RecordID record, const map<string, double>& measures);
			void Lookup(const string& measure, const Data::RIDList& records, vector<double>& results);
		};
	}
}

#endif