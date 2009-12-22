/*
 *  BDB.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "BDB.h"

BDB::BDB(const string& path, const string& name) {
	this->path = path;
	this->name = name;
	this->database = tcbdbnew();
}

BDB::~BDB() {
	this->Close();
  tcbdbdel(this->database);
}

bool BDB::Create(const string& path, const string& name) {
	TCBDB* database = tcbdbnew();
	
	tcbdbtune(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(database, BDB::Path(path, name).c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(database);
		tcbdbdel(database);
		return true;
	} else {
		tcbdbdel(database);
		return false;
	}
}

string BDB::Path(const string& path, const string& name) {
  return path + "/" + name + ".tcb";
}

bool BDB::OpenReader() {
  return this->Open(BDBOREADER);
}

bool BDB::OpenWriter() {
  return this->Open(BDBOWRITER | BDBOCREAT);
}

bool BDB::Truncate() {
	if(this->Open(BDBOWRITER | BDBOTRUNC)) {
		this->Close();
		return true;
	} else {
		return false;
	}
}

bool BDB::Open(int mode) {
	return tcbdbopen(this->database, BDB::Path(this->path, this->name).c_str(), mode);
}

bool BDB::Close() {
	if(tcbdbrnum(this->database) % (1<<16) == 0) {
		tcbdboptimize(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	}
	
	return tcbdbclose(this->database);
}

bool BDB::Get(const string& key, string& result) {
	int b_size;
	void* buffer;
	
	buffer = tcbdbget(this->database, key.c_str(), key.size(), &b_size);
	
	if(buffer == NULL) {
		return false;
	} else {
		result.assign((char*)buffer, b_size);
		free(buffer);
		return true;
	}
}

bool BDB::Get(const string& key, set<string>& results) {
	TCLIST* values = tcbdbget4(this->database, key.c_str(), key.size());
	
	if(values != NULL) {
		const char* value;
		size_t list_size = tclistnum(values);
    for(size_t i = 0; i < list_size; i++) {
			value = tclistval2(values, i);
			if(value != NULL) { results.insert(value); }
    }
    tclistdel(values);
		return true;
  } else {
		return false;
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
		return false;
	}
}

bool BDB::Get(const string& key, RIDList& results) {
	int size = (int)sizeof(RecordID);
	void* records = tcbdbget(this->database, key.c_str(), key.size(), &size);
	
	if(records != NULL) {
		size_t count = size / sizeof(RecordID);
		results.insert(results.end(), (RecordID*)records, (RecordID*)records + count);
		free(records);
		return true;
	} else {
		return false;
	}
}

bool BDB::Put(const string& key, const string& value) {
	return tcbdbput(this->database, key.c_str(), key.size(), value.c_str(), value.size());
}

bool BDB::PutDup(const string& key, const string& value) {
	return tcbdbputdup(this->database, key.c_str(), key.size(), value.c_str(), value.size());
}

bool BDB::PutCat(const string& key, const RecordID& value) {
	return tcbdbputcat(this->database, key.c_str(), key.size(), &value, sizeof(RecordID));
}

bool BDB::Add(const string& key, const int value, int& result) {
	result = tcbdbaddint(this->database, key.c_str(), key.length(), value);
	
	if(isnan(result)) {
		return false;
	} else {
		return true;
	}
}

bool BDB::Add(const string& key, const double value, double& result) {
	result = tcbdbadddouble(this->database, key.c_str(), key.length(), value);
	
	if(isnan(result)) {
		return false;
	} else {
		return true;
	}
}

/*
 * Returns the last error to occur on the database
 */
string BDB::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}

int BDB::ErrorCode() {
	return tcbdbecode(this->database);
}