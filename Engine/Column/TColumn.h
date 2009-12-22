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
#include "Engine/Column/Base.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		namespace Column {
			template <typename T>
			class TColumn : public Column::Base, public vector<T> {
			public:
				TColumn(const string& name) : Column::Base::Base(name) {}
				string Inspect();
			};
		}
	}
}

template <typename T> 
string Engine::Column::TColumn<T>::Inspect() {
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