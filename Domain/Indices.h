/*
 *  Indices.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/16/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_indices_h_
#define _flow_domain_data_indices_h_

#include <Common.h>
#include <Conditions.h>
#include <Domain/Data/Meta.h>
#include <Domain/Data/Index.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>
#include <Domain/Data/RIDMap.h>
#include <Domain/Data/RIDTree.h>

using namespace std;
using namespace Flow;
namespace Data = Flow::Domain::Data;

namespace Flow {
	namespace Domain {
		class Indices {
		protected:
			Data::Meta* meta;
			
			Indices();			
			bool Allocate(const Data::Record& record);
			
		public:
			Indices(Data::Meta* meta);
			
			virtual bool Insert(const Data::Record& record);
			virtual bool Lookup(const ValueMap& specified, Data::RIDList& results);
			virtual bool Lookup(const set<string>& dimensions, const Conditions& conditions, Data::RIDTree& results);
		};
	}
}

#endif