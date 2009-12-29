/*
 *  Base.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/18/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Base.h"

Domain::Base::Base(const string& path, const string& dpath) {
	this->path = path;
	this->dpath = dpath;
	this->meta = new Domain::Data::Meta(this->path);
	this->indices = new Domain::Indices(this->meta);
	this->dimensions = new Domain::Dimensions(this->dpath);
	this->measures = new Domain::Measures(this->dpath);
}

Domain::Base::~Base() {
	delete(this->measures);
	delete(this->dimensions);
	delete(this->indices);
	delete(this->meta);
}
