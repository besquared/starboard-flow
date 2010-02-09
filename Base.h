/*
 *  Base.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_base_h_
#define _flow_base_h_

#include <Common.h>

#include <Domain/Indices.h>
#include <Domain/Measures.h>
#include <Domain/Dimensions.h>
#include <Domain/Data/Meta.h>
#include <Engine/ResultSet.h>

namespace Flow {
  using namespace std;
  using namespace Flow::Domain;
  using namespace Flow::Domain::Data;
  
	class Base {
	protected:
		string path;

	public:
		Meta* meta;
		Indices* indices;
		Measures* measures;
		Dimensions* dimensions;
		
		Base(const string& path);
		~Base();
		
		bool Insert(const Record& record, const map<string, double>& measures);
	};
}

#endif