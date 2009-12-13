#include "ShellFragment.h"

ShellFragment::ShellFragment(const string& path) {
  this->path = path;
	this->opened = false;
	this->writer = false;
  this->database = tcbdbnew();
}

ShellFragment::~ShellFragment() {
  this->Close();
  tcbdbdel(this->database);
}

/*
 * I/O Management
 */
tuple<bool, string> ShellFragment::Create() {
	tcbdbtune(this->database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> ShellFragment::OpenReader() {
  return this->Open(false);
}

tuple<bool, string> ShellFragment::OpenWriter() {
  return this->Open(true);
}

tuple<bool, string> ShellFragment::Open(bool writer) {
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

tuple<bool, string> ShellFragment::Close() {
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

tuple<bool, string> ShellFragment::Truncate() {
	if(tcbdbopen(this->database, this->Path().c_str(), BDBOWRITER | BDBOTRUNC)) {
		tcbdbclose(this->database);
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}	
}

string ShellFragment::Path() {
  return this->path + "/" + "fragments.tcb";
}

/*
 * Reading
 */ 

string ShellFragment::Get(const string& key) {
  return this->Intern(this->GetRaw(key));
}

int ShellFragment::GetInt(const string& key) {
	return this->InternInt(this->GetRaw(key));
}

double ShellFragment::GetDouble(const string& key) {
	return this->InternDouble(this->GetRaw(key));
}

char *ShellFragment::GetRaw(const string& key) {
  return tcbdbget2(this->database, key.c_str());
}

vector<string> ShellFragment::GetList(const string& key) {
  return this->InternList(this->GetListRaw(key));
}

TCLIST *ShellFragment::GetListRaw(const string& key) {
  return tcbdbget4(this->database, key.c_str(), key.length());
}

vector<RecordID> ShellFragment::GetRecordIdList(const string& key) {
	return this->InternRecordIdList(this->GetListRaw(key));
}

vector<RecordID> ShellFragment::GetRecordIdList(const vector<string>& keys) {
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
        intersected = this->IntersectRecordIdLists(intersected, record_ids);
        tclistdel(stored);
      }
    }
  }
	
	return this->InternRecordIdList(intersected);
}

/*
 * Writing
 */

tuple<bool, string, int> ShellFragment::AddInt(const string& key, int value) {
	int newvalue = tcbdbaddint(this->database, key.c_str(), key.length(), value);

	if(newvalue != INT_MIN) {
		return make_tuple(ok, success, newvalue);
	} else {
		return make_tuple(error, this->Error(), newvalue);
	}
}

tuple<bool, string, double> ShellFragment::AddDouble(const string& key, double value) {
	double newvalue = tcbdbadddouble(this->database, key.c_str(), key.length(), value);
	
	if(isnan(newvalue)) {
		return make_tuple(error, this->Error(), newvalue);
	} else {
		return make_tuple(ok, success, newvalue);
	}
}

tuple<bool, string> ShellFragment::Put(const string& key, const string& value) {
#ifdef DEBUG
	cout << "ShellFragment::Put(" << key << ", " << value << ")" << endl;
#endif
	if(tcbdbput2(this->database, key.c_str(), value.c_str())) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> ShellFragment::PutDup(const string& key, const string& value) {
#ifdef DEBUG
	cout << "ShellFragment::PutDup(" << key << ", " << value << ")" << endl;
#endif
	
	if(tcbdbputdup2(this->database, key.c_str(), value.c_str())) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> ShellFragment::PutRecordID(const string& key, RecordID value) {
#ifdef DEBUG
	cout << "ShellFragment::PutRecordID(" << key << ", " << value << ")" << endl;
#endif
	
	if(tcbdbputdup(this->database, key.c_str(), key.size(), &value, sizeof(RecordID))) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> ShellFragment::PutList(const string& key, const vector<string>& values) {
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

tuple<bool, string> ShellFragment::TransactionBegin() {
	if(tcbdbtranbegin(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> ShellFragment::TransactionAbort() {
	if(tcbdbtranabort(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

tuple<bool, string> ShellFragment::TransactionCommit() {
	if(tcbdbtrancommit(this->database)) {
		return make_tuple(ok, success);
	} else {
		return make_tuple(error, this->Error());
	}
}

/*
 * Keys
 */

vector<string> ShellFragment::Keys() {
	return this->Keys("");
}

vector<string> ShellFragment::Keys(const string& prefix) {
	return(this->Keys(prefix, -1));
}

vector<string> ShellFragment::Keys(const string& prefix, int max) {
	TCLIST *keys = tcbdbfwmkeys2(this->database, prefix.c_str(), max);
	return this->InternList(keys);
}

/*
 * Error Management
 */

string ShellFragment::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}

/*
 * Data Conversion
 */

string ShellFragment::Intern(char *element) {
  string result;
  if(element != NULL) { 
    result = string(element);
    free(element);
  }
  return result;
}

int ShellFragment::InternInt(char *element) {
	int result = *((int*)(element));
	free(element);
	return result;
}

double ShellFragment::InternDouble(char *element) {
	double result = *((double*)(element));
	free(element);
	return result;	
}

vector<string> ShellFragment::InternList(TCLIST *list) {
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

vector<RecordID> ShellFragment::InternRecordIdList(TCLIST *list) {
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

TCLIST *ShellFragment::IntersectRecordIdLists(TCLIST *a, TCLIST *b) {
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
