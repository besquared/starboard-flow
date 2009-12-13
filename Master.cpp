/*
 *  Master.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 12/13/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Master.h"

Master::Master(const string& path) {
	this->path = path;
	this->database = tcbdbnew();
}

Master::~Master() {
	this->Close();
  tcbdbdel(this->database);
}

tuple<bool, string> Master::Create() {
	tcbdbtune(this->database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Master::OpenReader() {
  return this->Open(false);
}

tuple<bool, string> Master::OpenWriter() {
  return this->Open(true);
}

tuple<bool, string> Master::Open(bool writer) {
	int mode = (writer ? (BDBOWRITER | BDBOCREAT) : BDBOREADER);
	
	if(tcbdbopen(this->database, this->Path().c_str(), mode)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Master::Close() {
	if(tcbdbrnum(this->database) % (1<<16) == 0) {
		tcbdboptimize(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	}
	
  if(tcbdbclose(this->database)){
		return make_tuple(ok, success);
  } else {
    return make_tuple(error, this->Error());
  }
}

tuple<bool, string> Master::Truncate() {
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOTRUNC)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

string Master::Path() {
  return this->path + "/" + "master.tcb";
}

double Master::EventCount() {
	return 0.0;
}

vector<string> Master::Fragments() {
	vector<string> results;
	return results;
}

vector<string> Master::Dimensions(const string& fragment) {
	vector<string> results;
	return results;
}

vector<string> Master::Fragment(const string& dimension) {
	vector<string> results;
	return results;
}

tuple<bool, string> Master::Allocate(const set<string>& dimensions) {
	return make_tuple(ok, success);
}

tuple<bool, string, RecordID> Master::GenerateRecordID() {
	return make_tuple(ok, success, 0);
}

/*
 * Errors
 */
string Master::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}
