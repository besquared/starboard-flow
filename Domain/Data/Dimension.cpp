/*
 *  Dimension.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimension.h"

Domain::Data::Dimension::Dimension(const string& path, const string& name) {
  this->path = path;
  this->name = name;
  this->database = tchdbnew();
}

Domain::Data::Dimension::~Dimension() {
  this->Close();
  tchdbdel(this->database);	
}

string Domain::Data::Dimension::Path() {
  return this->path + "/" + this->name + ".tch";
}

/*
 * I/O Management
 */

bool Domain::Data::Dimension::Create() {
	tchdbtune(database, -1, -1, -1, HDBTLARGE | HDBTDEFLATE);
	if(this->Open(HDBOWRITER | HDBOCREAT)) {
		this->Close();
		return true;
	} else {
		return false;
	}
}

bool Domain::Data::Dimension::Truncate() {
	if(this->Open(HDBOWRITER | HDBOTRUNC)) {
		this->Close();
		return true;
	} else {
		return false;
	}	
}

bool Domain::Data::Dimension::Close() {	
  if(tchdbclose(this->database)){
		return true;
  } else {
    return false;
  }
}

bool Domain::Data::Dimension::Optimize() {
	if(tchdbrnum(this->database) % (1<<16) == 0) {
		return tchdboptimize(database, -1, -1, -1, HDBTLARGE | HDBTDEFLATE);
	} else {
		return false;
	}
}

bool Domain::Data::Dimension::OpenReader() {
  return this->Open(HDBOREADER);
}

bool Domain::Data::Dimension::OpenWriter() {
  return this->Open(HDBOWRITER | HDBOCREAT);
}

bool Domain::Data::Dimension::Open(int mode) {
	return tchdbopen(this->database, this->Path().c_str(), mode);
}

/*
 * Reading
 */ 

void Domain::Data::Dimension::Lookup(const RecordID key, string& result) {
	int vsize;
	void* value = tchdbget(this->database, &key, sizeof(RecordID), &vsize);
	
	if(value == NULL) {
		result = string("NULL");
	} else {
		result = string((char*)value, (size_t)vsize);
		free(value);
	}
}

void Domain::Data::Dimension::Lookup(const RIDList& keys, vector<string>& results) {
	results.reserve(keys.size());
	
	int written = 0;
	int bsize = 1024;
	void* buffer = malloc(bsize * sizeof(char));
	
	RIDList::const_iterator key;
	for(key = keys.begin(); key != keys.end(); key++) {
		written = tchdbget3(this->database, &(*key), sizeof(RecordID), buffer, bsize);
		if(written == -1) {
			results.push_back(NULL);
		} else {
			results.push_back(string((char*)buffer, (size_t)written));
		}
	}
	
	free(buffer);
}

void Domain::Data::Dimension::Lookup(const RIDList& keys, map<RecordID, string>& results) {
	int written = 0;
	int bsize = 4096;
	void* buffer = malloc(bsize * sizeof(char));
	
	RIDList::const_iterator key;
	for(key = keys.begin(); key != keys.end(); key++) {
		written = tchdbget3(this->database, &(*key), sizeof(RecordID), buffer, bsize);
		if(written == -1) {
			results[*key] = string(NULL);
		} else {
			results[*key] = string((char*)buffer, (size_t)written);
		}
	}
	
	free(buffer);	
}

/*
 * Writing
 */

bool Domain::Data::Dimension::Insert(const RecordID key, const string& value) {
	return tchdbput(this->database, &key, sizeof(RecordID), value.c_str(), value.size());
}

/*
 * Error Management
 */

string Domain::Data::Dimension::Error() {
	return string(tchdberrmsg(tchdbecode(this->database)));
}