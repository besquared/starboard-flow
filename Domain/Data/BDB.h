/*
 *  BDB.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_domain_data_bdb_h_
#define _flow_domain_data_bdb_h_

#include "Common.h"
#include "Domain/Data/RIDList.h"

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Domain {
		namespace Data {
			class BDB {
			protected:
				string path;
				string name;
				TCBDB *database;
				
			public:
				BDB(const string& path, const string& name);
				virtual ~BDB();
				
				virtual bool OpenReader();
				virtual bool OpenWriter();
				virtual bool Open(int mode);
				virtual bool Close();
				virtual bool Truncate();
				
				virtual bool Get(const string& key, string& result);
				virtual bool Get(const string& key, set<string>& results);
				virtual bool Get(const string& key, vector<string>& results);
				virtual bool Get(const string& key, RIDList& results);
				
				virtual bool Put(const string& key, const string& value);
				virtual bool PutDup(const string& key, const string& value);
				virtual bool PutCat(const string& key, const RecordID& record);
				
				virtual bool Add(const string& key, const int value, int& result);
				virtual bool Add(const string& key, const double value, double& result);
				
				string Error();
				int ErrorCode();
				
				static bool Create(const string& path, const string& name);
				static string Path(const string& path, const string& name);
			};
		}
	}
}

#endif