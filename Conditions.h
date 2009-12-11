/*
 *  Conditions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _conditions_included_
#define _conditions_included_

#include "Common.h"
#include "Condition.h"

#include "EQ.h"
#include "IN.h"
#include "GT.h"
#include "GTE.h"
#include "LT.h"
#include "LTE.h"

namespace Flow {
  class Conditions : public vector< shared_ptr<Condition> > {
  public:
		map<string, int>* conditions;
		
    Conditions();
		~Conditions();

		/*
		 * Modifying
		 */
		void push_back(const string& column, const string& value);
		void push_back(const string& name, shared_ptr<Condition> column);
		
		void erase(const string& name);
		
		/*
		 * Accessing
		 */
		shared_ptr<Condition> at(int position);
		shared_ptr<Condition> at(const string& name);
		shared_ptr<Condition> operator[](int position);
		shared_ptr<Condition> operator[](const string& name);
		shared_ptr<Condition> operator[](const char* name);
		
		/*
		 * Indexing
		 */
		bool exist(const string& name);
		int position(const string& name);
		
		/*
		 * Application
		 */
		void Apply(const string& column, vector<string>& values);
		
	protected:
		void push_back(shared_ptr<Condition> column); 
  };
}

#endif