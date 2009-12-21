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
	this->meta = new Meta(path);
	this->indices = new Indices(meta);
	this->measures = new Measures(path);
	this->dimensions = new Dimensions(path);
}

Base::~Base() {
	delete(this->indices);
	delete(this->measures);
	delete(this->dimensions);
}

bool Base::Insert(const Record& record, const map<string, double>& measures) {
	if(!this->dimensions->Insert(record)) { return false;	}
	if(!this->measures->Insert(record.id, measures)) { return false; }
	if(!this->indices->Insert(record)) { return false; }
	return true;
}