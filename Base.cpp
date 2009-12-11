/*
 *  Base.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Base.h"

Base::Base(const string& path) {
	this->path = path;
	this->dimensions = new Dimensions(path);
	this->measures = new Measures(path);
	this->fragments = new ShellFragments(path);
}

Base::~Base() {
	delete(this->measures);
	delete(this->fragments);
}

tuple<bool, string> Base::Insert(RecordID record, 
																 const map<string, string>& dimensions, 
																 const map<string, double>& measures) {

	Response opened;
	Response inserted;
	
	inserted = this->dimensions->Insert(record, dimensions);
	
	if(!inserted.get<0>()) {
		return inserted;
	}
	
	inserted = this->measures->Insert(record, measures);
	
	if(!inserted.get<0>()) {
		return inserted;
	}
	
	opened = this->fragments->OpenWriter();
	
	if(!opened.get<0>()) {
		return opened;
	}
	
	inserted = this->fragments->Insert(record, dimensions);
	
	if(!inserted.get<0>()) {
		return inserted;
	}
	
	this->fragments->Close();

	return make_tuple(ok, success);
}

tuple< bool, string, shared_ptr<Table> > Base::Query(const map<string, string>& conditions) {
	
}