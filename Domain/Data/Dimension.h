/*
 *  Dimension.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_dimension_h_
#define _flow_domain_data_dimension_h_

#include <Common.h>
#include <Domain/Data/RIDList.h>

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		namespace Data {
			class Dimension {
			public:
				string path;
				string name;
				TCHDB* database;
				
				Dimension(const string& path, const string& name);
				~Dimension();
				string Path();

				/*
				 * I/O Management
				 */
				bool Create();
				bool Truncate();
				bool Close();
				bool Optimize();
				bool OpenReader();
				bool OpenWriter();
				bool Open(int mode);
				
				/*
				 * Reading
				 */
				void Lookup(const RecordID key, string& result);
				void Lookup(const RIDList& keys, vector<string>& results);
				void Lookup(const RIDList& keys, map<RecordID, string>& results);

				/*
				 * Writing
				 */
				bool Insert(const RecordID key, const string& value);
				
				/*
				 * Error Handling
				 */
				string Error();
			};
		}
	}
}

#endif