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
	this->opened = false;
	this->writer = false;
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
	
	if(this->opened) {
		if(writer && this->writer) {
			return make_tuple(ok, success);
		} else if(!writer && !this->writer) {
			return make_tuple(ok, success);
		} else {
			return make_tuple(error, "Database is already open in the wrong mode.");
		}
	}
	
	if(tcbdbopen(this->database, this->Path().c_str(), mode)) {
		this->opened = true;
		this->writer = (writer ? true : false);
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
		this->opened = false;
		this->writer = false;
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

/*
 * Reading
 */ 

string Fragment::Get(const string& key) {
  return this->Intern(this->GetRaw(key));
}

int Fragment::GetInt(const string& key) {
	return this->InternInt(this->GetRaw(key));
}

double Fragment::GetDouble(const string& key) {
	return this->InternDouble(this->GetRaw(key));
}

char *Fragment::GetRaw(const string& key) {
  return tcbdbget2(this->database, key.c_str());
}

vector<string> Fragment::GetList(const string& key) {
  return this->InternList(this->GetListRaw(key));
}

TCLIST *Fragment::GetListRaw(const string& key) {
  return tcbdbget4(this->database, key.c_str(), key.length());
}

vector<RecordID> Fragment::GetRecords(const string& key) {
	return this->InternRecords(this->GetListRaw(key));
}

vector<RecordID> Fragment::GetRecords(const vector<string>& keys) {
	if(keys.empty()) { return vector<RecordID>(); }
  
  TCLIST *intersected = this->GetListRaw(keys[0]);
  
  if(intersected != NULL) {
    for(size_t i = 1; i < keys.size(); i++) {
      TCLIST *record_ids = this->GetListRaw(keys[i]);
			
      if(record_ids == NULL) {
        if(intersected != NULL) {
          tclistdel(intersected);
        }
				
        return vector<RecordID>();
      } else {
        TCLIST *stored = intersected;
        intersected = this->IntersectRecords(intersected, record_ids);
        tclistdel(stored);
      }
    }
  }
	
	return this->InternRecords(intersected);
}

/*
 * Writing
 */

tuple<bool, string, int> Fragment::AddInt(const string& key, int value) {
	int newvalue = tcbdbaddint(this->database, key.c_str(), key.length(), value);
	
	if(newvalue != INT_MIN) {
		return make_tuple(ok, success, newvalue);
	} else {
		return make_tuple(error, this->Error(), newvalue);
	}
}

tuple<bool, string, double> Fragment::AddDouble(const string& key, double value) {
	double newvalue = tcbdbadddouble(this->database, key.c_str(), key.length(), value);
	
	if(isnan(newvalue)) {
		return make_tuple(error, this->Error(), newvalue);
	} else {
		return make_tuple(ok, success, newvalue);
	}
}

tuple<bool, string> Fragment::Put(const string& key, const string& value) {
	if(tcbdbput2(this->database, key.c_str(), value.c_str())) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::PutDup(const string& key, const string& value) {
	if(tcbdbputdup2(this->database, key.c_str(), value.c_str())) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::PutRecord(const string& key, RecordID value) {
	if(tcbdbputdup(this->database, key.c_str(), key.size(), &value, sizeof(RecordID))) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::PutList(const string& key, const vector<string>& values) {
	tuple<bool, string> written;
	size_t list_size = values.size();
	for(size_t i = 0; i < list_size; i++) {
		written = this->PutDup(key, values[i]);
		if(!written.get<0>()) {
			return make_tuple(error, this->Error());
		}
	}
	
	return make_tuple(ok, success);
}

/*
 * Transactions
 */

tuple<bool, string> Fragment::TransactionBegin() {
	if(tcbdbtranbegin(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::TransactionAbort() {
	if(tcbdbtranabort(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> Fragment::TransactionCommit() {
	if(tcbdbtrancommit(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

/*
 * Keys
 */

vector<string> Fragment::Keys() {
	return this->Keys("");
}

vector<string> Fragment::Keys(const string& prefix) {
	return(this->Keys(prefix, -1));
}

vector<string> Fragment::Keys(const string& prefix, int max) {
	TCLIST *keys = tcbdbfwmkeys2(this->database, prefix.c_str(), max);
	return this->InternList(keys);
}

/*
 * Error Management
 */

string Fragment::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}

/*
 * Data Conversion
 */

string Fragment::Intern(char *element) {
  string result;
  if(element != NULL) { 
    result = string(element);
    free(element);
  }
  return result;
}

int Fragment::InternInt(char *element) {
	int result = *((int*)(element));
	free(element);
	return result;
}

double Fragment::InternDouble(char *element) {
	double result = *((double*)(element));
	free(element);
	return result;	
}

vector<string> Fragment::InternList(TCLIST *list) {
  vector<string> results;
  
  if(list != NULL) {
		size_t list_size = tclistnum(list);
    for(size_t i = 0; i < list_size; i++) {
      results.push_back(tclistval2(list, i));
    }
    tclistdel(list);
  }
  
  return results;
}

vector<RecordID> Fragment::InternRecords(TCLIST *list) {
	vector<RecordID> results;
	int esize = (int)sizeof(RecordID);
	
  if(list != NULL) {
		size_t list_size = tclistnum(list);
    for(size_t i = 0; i < list_size; i++) {
      results.push_back(*((RecordID*)tclistval(list, i, &esize)));
    }
    tclistdel(list);
  }
  
  return results;	
}

/*
 * Utility
 */

TCLIST *Fragment::IntersectRecords(TCLIST *a, TCLIST *b) {
  TCLIST *result = tclistnew();
  
  if(a == NULL || b == NULL) return result;
  
  int aindex = 0;
  int bindex = 0;
  int alength = tclistnum(a);
  int blength = tclistnum(b);
	
	int esize = sizeof(RecordID);
  while(aindex < alength && bindex < blength) {
    RecordID *avalue = (RecordID*)tclistval(a, aindex, &esize);
		RecordID *bvalue = (RecordID*)tclistval(b, bindex, &esize);
		
    if(*avalue == *bvalue) {
      tclistpush(result, avalue, sizeof(RecordID));
      aindex++;  
      bindex++;  
    } else if(*avalue < *bvalue) {  
      aindex++;  
    } else {  
      bindex++;  
    }
  }
	
  return result;
}