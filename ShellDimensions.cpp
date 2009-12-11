#include "ShellDimensions.h"

ShellDimensions::ShellDimensions(ShellFragment *database) {
  this->database = database;
}

tuple<bool, string> ShellDimensions::Create(const string& fragment, const string& name) {
	// Keep a list of all the dimensions in the index
	tuple<bool, string> written;
	written = this->database->PutDup(this->DimensionsKey(), name);
	if(!written.get<0>()) {
		return make_tuple(error, "Dimension creation failed: " + this->database->Error());
	}
	
	// Keep a list of all the dimensions for this fragment	
	written = this->database->PutDup(this->DimensionsKey(fragment), name);
	if(!written.get<0>()) {
		return make_tuple(error, "Dimension creation failed: " + this->database->Error());
	}
	
	// Keep a record of the fragment for this dimension
	written = this->database->Put(this->FragmentKey(name), fragment);
	if(!written.get<0>()) {
		return make_tuple(error, "Dimension creation failed: " + this->database->Error());
	}
	
	return make_tuple(ok, success);
}

tuple<bool, string> ShellDimensions::Insert(const string& name, const string& value) {
	tuple<bool, string, int> added = this->database->AddInt(this->ValueKey(name, value), 1);
	
	int count;
	if(added.get<0>()) {
		count = added.get<2>();
	} else {
		return make_tuple(error, "Dimension insertion failed: " + added.get<1>());
	}
	
	if(count == 1) {
		tuple<bool, string> written = this->database->PutDup(this->ValuesKey(name), value);
		
		if(written.get<0>()) {
			return make_tuple(ok, success);
		} else {
			return make_tuple(error, "Dimension insertion failed: " + written.get<1>());
		}
	} else {
		return make_tuple(ok, success);
	}
}

vector<string> ShellDimensions::List() {
  return this->database->GetList(this->DimensionsKey());
}

vector<string> ShellDimensions::List(const string& fragment) {
  return this->database->GetList(this->DimensionsKey(fragment));
}

vector<string> ShellDimensions::Values(const string& dimension) {
  string key = this->ValuesKey(dimension);
	return this->database->GetList(key);
}

string ShellDimensions::Fragment(const string& dimension) {
  return this->database->Get(this->FragmentKey(dimension));
}

/*
 * Keys
 */
string ShellDimensions::DimensionsKey() {
	return "[dimensions]";
}

// fragment has-many dimensions
string ShellDimensions::DimensionsKey(const string& fragment) {
	return fragment + ":[dimensions]";
}

// dimension belongs-to fragment
string ShellDimensions::FragmentKey(const string& name) {
	return "[dimensions]:" + name;
}

// fragment has-many values, through => dimension
string ShellDimensions::ValuesKey(const string& name) {
	return "[" + name + "]";
}

// value belongs-to dimension
// Helps us keep a unique set of dimensions
string ShellDimensions::ValueKey(const string& name, const string& value) {
	return this->ValuesKey(name) + ":" + value;
}
