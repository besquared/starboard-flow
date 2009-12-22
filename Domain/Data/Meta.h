/*
 *  Meta.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/13/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_meta_h_
#define _flow_domain_data_meta_h_

#define FRAGMENT_SIZE 4

#include "Common.h"
#include "Domain/Data/BDB.h"
#include "Domain/Data/Index.h"

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		namespace Data {
			class Meta : public Domain::Data::BDB {
			public:
				Domain::Data::Index *index;

				Meta(const string& path);
				~Meta();
				
				virtual bool Indices(vector<string>& results);		
				virtual bool Index(const string& dimension, string& result);

				virtual bool Dimensions(set<string>& results);
				virtual bool Dimensions(const string& fragment, set<string>& results);
				virtual bool Dimensions(const set<string>& fragment, set<string>& results);
				
				virtual bool Allocate(const set<string>& dimensions);
				virtual bool GenerateRecordID(RecordID& result);
				static bool Create(const string& path);
			};
		}
	}
}

#endif