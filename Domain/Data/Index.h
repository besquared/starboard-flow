/*
 *  Index.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_index_h_
#define _flow_domain_data_index_h_

#include "Common.h"
#include "Domain/Data/BDB.h"
#include "Domain/Data/Record.h"
#include "Domain/Data/RIDList.h"
#include "Domain/Data/RIDMap.h"

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		namespace Data {
			class Index : public Domain::Data::BDB {
			public:		
				Index(const string& path);		
				
				static bool Create(const string& path);
				
				/*
				 * Returns a list of records corresponding to the specified dimension values
				 */
				virtual bool Lookup(const map<string, string>& dimensions, RIDList& results);
				
				/*
				 * Returns a set of values for each given dimension as a map
				 */
				virtual bool Lookup(const set<string>& dimensions, ValuesMap& results);
				
				/*
				 * Returns record lists for the given dimension for each given value
				 */
				virtual bool Lookup(const string& dimension, const vector<string>& values, RIDMap& results);
				
				/*
				 * Inserts a single row into the index
				 */
				virtual bool Insert(const Record& record);
				
				/*
				 * Uniquely inserts a set of dimensions and their values
				 */
				virtual bool InsertValues(const Record& record);
				
				string Key(const string& component);
				string Key(const vector<string>& components);
				string ValuesKey(const string& dimension);
				string ValueKey(const string& dimension, const string& value);
				string Component(const string& dimension, const string& value);
				
				vector< vector<string> > PowerSet(vector<string>& values);
				bool IsSet(const unsigned int *set, int i);
			};
		}
	}
}

#endif