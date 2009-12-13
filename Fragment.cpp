/*
 *  Fragment.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Fragment.h"

Fragment::Fragment(const string& path) {
  this->path = path;
  this->database = tcbdbnew();
}

Fragment::~Fragment() {
  this->Close();
  tcbdbdel(this->database);
}

/*
 * I/O Management
 */
tuple<bool, string> Fragment::Create() {
	tcbdbtune(this->database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::OpenReader() {
  return this->Open(false);
}

tuple<bool, string> Fragment::OpenWriter() {
  return this->Open(true);
}

tuple<bool, string> Fragment::Open(bool writer) {
	int mode = (writer ? (BDBOWRITER | BDBOCREAT) : BDBOREADER);
	
	if(tcbdbopen(this->database, this->Path().c_str(), mode)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::Close() {
	if(tcbdbrnum(this->database) % (1<<16) == 0) {
		tcbdboptimize(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	}
	
  if(tcbdbclose(this->database)){
		return make_tuple(ok, success);
  } else {
    return make_tuple(error, this->Error());
  }
}

tuple<bool, string> Fragment::Truncate() {
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOTRUNC)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

string Fragment::Path() {
  return this->path + "/" + "fragments.tcb";
}

string Fragment::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}
