/*
 *  MeasureDB.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measure.h"

Measure::Measure(string path, string name) {
  this->path = path;
  this->name = name;
  this->database = tcfdbnew();
	
	int64_t size_limit = (1LL << 30);
	tcfdbtune(this->database, sizeof(double), size_limit);
}

Measure::~Measure() {
  this->Close();
  tcfdbdel(this->database);
}

/*
 * I/O Management
 */

tuple<bool, string> Measure::Create() {
	if(tcfdbopen(this->database, this->Path().c_str(), FDBOWRITER | FDBOCREAT)) {
		tcfdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

tuple<bool, string> Measure::OpenReader() {
  return this->Open(false);
}

tuple<bool, string> Measure::OpenWriter() {
  return this->Open(true);
}

tuple<bool, string> Measure::Open(bool writer) {
	int mode = (writer ? (FDBOWRITER | FDBOCREAT) : FDBOREADER);
	
	if(tcfdbopen(this->database, this->Path().c_str(), mode)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Measure::Close() {
  if(tcfdbclose(this->database)){
		return make_tuple(ok, success);
  } else {
    return make_tuple(error, this->Error());
  }
}

tuple<bool, string> Measure::Truncate() {
	if(tcfdbopen(this->database, this->Path().c_str(), FDBOWRITER | FDBOTRUNC)) {
		tcfdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

string Measure::Path() {
  return this->path + "/" + this->name + ".tcf";
}

/*
 * Reading
 */ 

double Measure::Get(RecordID key) {
	int size_v;
	void* value = tcfdbget(this->database, key, &size_v);
	
	if(value == NULL) {
		return NULL;
	} else {
		double result = *((double*)(value));
		free(value);
		return result;
	}
}

void Measure::Get(const vector<RecordID>& keys, vector<double>& results) {
	results.reserve(keys.size());
	
	double buffer;
	size_t size_k = keys.size();
	for(size_t i = 0; i < size_k; i++) {
		if(tcfdbget4(this->database, keys[i], &buffer, sizeof(double)) != -1) {
			results.push_back(buffer);
		}
	}
}

/*
 * Writing
 */

tuple<bool, string> Measure::Put(RecordID key, double value) {
	if(tcfdbput(this->database, key, &value, sizeof(double))) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

/*
 * Transactions
 */

bool Measure::TransactionBegin() {
	return tcfdbtranbegin(this->database);
}

bool Measure::TransactionAbort() {
	return tcfdbtranabort(this->database);
}

bool Measure::TransactionCommit() {
	return tcfdbtrancommit(this->database);
}

/*
 * Error Management
 */

string Measure::Error() {
	return string(tcfdberrmsg(tcfdbecode(this->database)));
}