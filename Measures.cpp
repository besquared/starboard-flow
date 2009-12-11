/*
 *  Measures.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measures.h"

Measures::Measures(const string& path) {
	this->path = path;
}

tuple< bool, string, shared_ptr<Measure> > Measures::Create(const string& name) {
	shared_ptr<Measure> measure(new Measure(this->path, name));
	tuple<bool, string> created = measure->Create();
	return make_tuple(created.get<0>(), created.get<1>(), measure);
}

tuple< bool, string, shared_ptr<Measure> > Measures::OpenReader(const string& name) {
	shared_ptr<Measure> measure(new Measure(this->path, name));
	tuple<bool, string> opened = measure->OpenReader();
	return make_tuple(opened.get<0>(), opened.get<1>(), measure);
}

tuple< bool, string, shared_ptr<Measure> > Measures::OpenWriter(const string& name) {
	shared_ptr<Measure> measure(new Measure(this->path, name));
	tuple<bool, string> opened = measure->OpenWriter();
	return make_tuple(opened.get<0>(), opened.get<1>(), measure);	
}

tuple<bool, string> Measures::Insert(RecordID record, const map<string, double>& measures) {
	map<string, double>::const_iterator measure;
	tuple< bool, string, shared_ptr<Measure> > opened;
	for(measure = measures.begin(); measure != measures.end(); measure++) {
		opened = this->OpenWriter(measure->first);
		if(opened.get<0>()) {
			shared_ptr<Measure> database = opened.get<2>();
			tuple<bool, string> written = database->Put(record, measure->second);
			database->Close();
			
			if(!written.get<0>()) {
				return make_tuple(error, written.get<1>());
			}
		} else {
			return make_tuple(error, opened.get<1>());
		}
	}
	
	return make_tuple(ok, success);
}
