/*
 *  Measure.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measure.h"

Domain::Data::Measure::Measure(string path, string name) {
  this->path = path;
  this->name = name;
  this->database = tcfdbnew();
}

Domain::Data::Measure::~Measure() {
  this->Close();
  tcfdbdel(this->database);
}

string Domain::Data::Measure::Path() {
  return this->path + "/" + this->name + ".tcf";
}

/*
 * I/O Management
 */

bool Domain::Data::Measure::Create() {	
	tcfdbtune(this->database, sizeof(double), INT_MAX);
	
	if(this->Open(FDBOWRITER | FDBOCREAT)) {
		this->Close();
		return true;
	} else {
		return false;
	}	
}

bool Domain::Data::Measure::Close() {
  if(tcfdbclose(this->database)){
		return true;
  } else {
    return false;
  }
}

bool Domain::Data::Measure::Truncate() {
	if(this->Open(FDBOWRITER | FDBOTRUNC)) {
		this->Close();
		return true;
	} else {
		return false;
	}	
}

bool Domain::Data::Measure::OpenReader() {
  return this->Open(FDBOREADER);
}

bool Domain::Data::Measure::OpenWriter() {
  return this->Open(FDBOWRITER | FDBOCREAT);
}

bool Domain::Data::Measure::Open(int mode) {
	return tcfdbopen(this->database, this->Path().c_str(), mode);
}

/*
 * Reading
 */ 

bool Domain::Data::Measure::Lookup(RecordID key, double& result) {
	int size_v;
	void* value = tcfdbget(this->database, key, &size_v);
	
	if(value == NULL) {
		return false;
	} else {
		result = *((double*)(value));
		free(value);
		return true;
	}
}

void Domain::Data::Measure::Lookup(const RIDList& keys, vector<double>& results) {
	results.reserve(keys.size());
	
	double buffer;
	RIDList::const_iterator key;
	for(key = keys.begin(); key != keys.end(); key++) {
		if(tcfdbget4(this->database, *key, &buffer, sizeof(double)) != -1) {
			results.push_back(buffer);
		}
	}
}

/*
 * Writing
 */

bool Domain::Data::Measure::Insert(RecordID key, double value) {
	return tcfdbput(this->database, key, &value, sizeof(double));
}

/*
 * Error Management
 */

string Domain::Data::Measure::Error() {
	return string(tcfdberrmsg(tcfdbecode(this->database)));
}