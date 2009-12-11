/*
 *  ListColumn.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _tlist_column_included_
#define _tlist_column_included_

#include "Common.h"
#include "Column.h"

namespace Flow {
	template <typename T>
  class TListColumn : public Column, public vector< vector<T> > {
	public:
		string Inspect();
		string Inspect(const vector<T>& tlist);
	};
}

template <typename T> 
string TListColumn<T>::Inspect() {
	string out;
	
	out += "[";
	for(size_t i = 0; i < this->size(); i++) {
		out += this->Inspect(this->at(i));
		if(i < this->size() - 1) out += ", "; 
	}
	out += "]";
	
	return out;	
}

template <typename T> 
string TListColumn<T>::Inspect(const vector<T>& tlist) {
	string out;
	
	out += "[";
	for(size_t i = 0; i < tlist.size(); i++) {
		out += lexical_cast<string>(tlist.at(i));
		if(i < tlist.size() - 1) out += ", "; 
	}
	out += "]";
	
	return out;	
}

#endif