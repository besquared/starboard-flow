/*
 *  TColumn.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/30/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _tcolumn_included_
#define _tcolumn_included_

#include "Common.h"
#include "Column.h"

namespace Flow {
	template <typename T>
  class TColumn : public Column, public vector<T> {
	public:
		string Inspect();
	};
}

template <typename T> 
string TColumn<T>::Inspect() {
	string out;
	
	out += "[";
	for(size_t i = 0; i < this->size(); i++) {
		out += lexical_cast<string>(this->at(i));
		if(i < this->size() - 1) out += ", "; 
	}
	out += "]";
	
	return out;	
}

#endif