/*
 *  RIDMap.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/19/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_rid_map_h_
#define _flow_domain_data_rid_map_h_

#include "Common.h"
#include "Domain/Data/RIDList.h"

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		namespace Data {
			class RIDMap : public map<string, Domain::Data::RIDList> {
			public:
				void operator&(Domain::Data::RIDList& records);
				void operator|(Domain::Data::RIDList& records);
			};
		}
	}
}

#endif