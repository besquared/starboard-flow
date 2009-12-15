/*
 *  Dimension.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimension.h"


Dimension::Dimension(string path, string name) {
  this->path = path;
  this->name = name;
  this->database = tchdbnew();
}

Dimension::~Dimension() {
  this->Close();
  tchdbdel(this->database);	
}

/*
 * I/O Management
 */

tuple<bool, string> Dimension::Create() {
	tchdbtune(database, -1, -1, -1, HDBTLARGE | HDBTDEFLATE);

	if(tchdbopen(this->database, this->Path().c_str(), HDBOWRITER | HDBOCREAT)) {
		tchdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

tuple<bool, string> Dimension::OpenReader() {
  return this->Open(false);
}

tuple<bool, string> Dimension::OpenWriter() {
  return this->Open(true);
}

tuple<bool, string> Dimension::Open(bool writer) {
	int mode = (writer ? (HDBOWRITER | HDBOCREAT) : HDBOREADER);
	if(tchdbopen(this->database, this->Path().c_str(), mode)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Dimension::Close() {
	if(tchdbrnum(this->database) % (1<<16) == 0) {
		tchdboptimize(database, -1, -1, -1, HDBTLARGE | HDBTDEFLATE);
	}
	
  if(tchdbclose(this->database)){
		return make_tuple(ok, success);
  } else {
    return make_tuple(error, this->Error());
  }
}

tuple<bool, string> Dimension::Truncate() {
	if(tchdbopen(this->database, this->Path().c_str(), HDBOWRITER | HDBOTRUNC)) {
		tchdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

string Dimension::Path() {
  return this->path + "/" + this->name + ".tch";
}

/*
 * Reading
 */ 

string Dimension::Get(RecordID key) {
	int vsize;
	void* value = tchdbget(this->database, &key, sizeof(RecordID), &vsize);
	
	if(value == NULL) {
		return string("NULL");
	} else {
		string result = string((char*)value, (size_t)vsize);
		free(value);
		return result;
	}
}

void Dimension::Get(const vector<RecordID>& keys, vector<string>& results) {
	results.reserve(keys.size());
	
	int written = 0;
	int bsize = 256;
	void* buffer = malloc(bsize * sizeof(char));
	size_t size_k = keys.size();
	for(size_t i = 0; i < size_k; i++) {
		written = tchdbget3(this->database, &keys[i], sizeof(RecordID), buffer, bsize);
		if(written == -1) {
			results.push_back(NULL);
		} else {
			results.push_back(string((char*)buffer, (size_t)written));
		}
	}
	
	free(buffer);
}

void Dimension::Get(const vector<RecordID>& keys, map<RecordID, string>& results) {
	int written = 0;
	int bsize = 4096;
	void* buffer = malloc(bsize * sizeof(char));
	size_t size_k = keys.size();
	for(size_t i = 0; i < size_k; i++) {
		written = tchdbget3(this->database, &keys[i], sizeof(RecordID), buffer, bsize);
		if(written == -1) {
			results[keys[i]] = string(NULL);
		} else {
			results[keys[i]] = string((char*)buffer, (size_t)written);
		}
	}
	
	free(buffer);	
}

/*
 * Writing
 */

tuple<bool, string> Dimension::Put(RecordID key, string value) {
#ifdef DEBUG
	cout << "Dimension::Put(" << key << ", " << value << ")" << endl;
#endif
	if(tchdbput(this->database, &key, sizeof(RecordID), value.c_str(), value.size())) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Dimension::PutAsync(RecordID key, string value) {
	if(tchdbputasync(this->database, &key, sizeof(RecordID), value.c_str(), value.size())) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

/*
 * Transactions
 */

bool Dimension::TransactionBegin() {
	return tchdbtranbegin(this->database);
}

bool Dimension::TransactionAbort() {
	return tchdbtranabort(this->database);
}

bool Dimension::TransactionCommit() {
	return tchdbtrancommit(this->database);
}

/*
 * Error Management
 */

string Dimension::Error() {
	return string(tchdberrmsg(tchdbecode(this->database)));
}