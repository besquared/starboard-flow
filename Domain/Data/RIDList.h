/*
 *  RIDList.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_rid_list_h_
#define _flow_domain_data_rid_list_h_

#include "Common.h"

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		namespace Data {
			class RIDList : public vector<RecordID> {
			public:
				RIDList();		
				RIDList operator&(RIDList& other);
				RIDList operator|(RIDList& other);
				string Inspect();
			};
		}
	}
}

#endif