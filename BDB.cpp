/*
 *  BDB.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "BDB.h"

BDB::BDB(const string& path) {
	this->path = path;
	this->database = tcbdbnew();
}

BDB::~BDB() {
	this->Close();
  tcbdbdel(this->database);
}

tuple<bool, string> BDB::Create() {
	tcbdbtune(this->database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> BDB::OpenReader() {
  return this->Open(false);
}

tuple<bool, string> BDB::OpenWriter() {
  return this->Open(true);
}

tuple<bool, string> BDB::Open(bool writer) {
	int mode = (writer ? (BDBOWRITER | BDBOCREAT) : BDBOREADER);
	
	if(tcbdbopen(this->database, this->Path().c_str(), mode)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> BDB::Close() {
	if(tcbdbrnum(this->database) % (1<<16) == 0) {
		tcbdboptimize(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	}
	
  if(tcbdbclose(this->database)){
		return make_tuple(ok, success);
  } else {
    return make_tuple(error, this->Error());
  }
}

/*
 * Clear this database of all key/value pairs
 */
tuple<bool, string> BDB::Truncate() {
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOTRUNC)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

bool BDB::Get(const string& key, string& result) {
	int* b_size;
	void* buffer = tcbdbget(this->database, key.c_str(), key.size(), b_size);
	
	if(buffer == NULL) {
		free(buffer);
		return false;
	} else {
		result.assign((char*)buffer, *b_size);
		free(buffer);
		return true;
	}
}

bool BDB::Get(const string& key, vector<string>& results) {
	TCLIST* values = tcbdbget4(this->database, key.c_str(), key.size());
	
	if(values != NULL) {
		const char* value;
		size_t list_size = tclistnum(values);
    for(size_t i = 0; i < list_size; i++) {
			value = tclistval2(values, i);
			if(value != NULL) { results.push_back(value); }
    }
    tclistdel(values);
		return true;
  } else {
		tclistdel(values);
		return false;
	}
}

bool BDB::Get(const string& key, vector<RecordID>& results) {
	int size = (int)sizeof(RecordID);
	TCLIST* values = tcbdbget4(this->database, key.c_str(), key.size());
	
	if(values != NULL) {
		const void* value;
		size_t list_size = tclistnum(values);
    for(size_t i = 0; i < list_size; i++) {
			value = tclistval(values, i, &size);
			if(value != NULL) {
				results.push_back(*((RecordID*)value));
			}
    }
    tclistdel(values);
		return true;
  } else {
		tclistdel(values);
		return false;
	}	
}

/*
 * Transactions
 */

tuple<bool, string> BDB::TransactionBegin() {
	if(tcbdbtranbegin(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> BDB::TransactionAbort() {
	if(tcbdbtranabort(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> BDB::TransactionCommit() {
	if(tcbdbtrancommit(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}


/*
 * Returns the last error to occur on the database
 */
string BDB::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}
