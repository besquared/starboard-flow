/*
 *  Dimensions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimensions.h"

Dimensions::Dimensions(const string& path) {
	this->path = path;
}

tuple< bool, string, shared_ptr<Dimension> > Dimensions::Create(const string& name) {
	shared_ptr<Dimension> dimension(new Dimension(this->path, name));
	tuple<bool, string> created = dimension->Create();
	return make_tuple(created.get<0>(), created.get<1>(), dimension);
}

tuple< bool, string, shared_ptr<Dimension> > Dimensions::OpenReader(const string& name) {
	shared_ptr<Dimension> dimension(new Dimension(this->path, name));
	tuple<bool, string> opened = dimension->OpenReader();
	return make_tuple(opened.get<0>(), opened.get<1>(), dimension);
}

tuple< bool, string, shared_ptr<Dimension> > Dimensions::OpenWriter(const string& name) {
	shared_ptr<Dimension> dimension(new Dimension(this->path, name));
	tuple<bool, string> opened = dimension->OpenWriter();
	return make_tuple(opened.get<0>(), opened.get<1>(), dimension);	
}

tuple<bool, string> Dimensions::Insert(RecordID record, const map<string, string>& dimensions) {
	map<string, string>::const_iterator dimension;
	tuple< bool, string, shared_ptr<Dimension> > opened;
	for(dimension = dimensions.begin(); dimension != dimensions.end(); dimension++) {
		opened = this->OpenWriter(dimension->first);
		if(opened.get<0>()) {
			shared_ptr<Dimension> database = opened.get<2>();
			bool written = database->Insert(record, dimension->second);
			database->Close();
			
			if(written) {
				return make_tuple(error, "failed");
			}
		} else {
			return make_tuple(error, "failed");
		}
	}
	
	return make_tuple(ok, success);
}
