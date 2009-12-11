/*
 *  Columns.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/30/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _columns_included_
#define _columns_included_

#include "Common.h"
#include "Column.h"
#include "Table.h"

namespace Flow {
	class Table;
	
  class Columns : public vector< shared_ptr<Column> > {
  public:
		Table* table;
		map<string, int>* columns;
		
    Columns(Table *table);
		
		/*
		 * Modifying
		 */
		void push_back(shared_ptr<Column> column);
		void push_back(const string& name, shared_ptr<Column> column);
		
		void erase(const string& name);
		
		/*
		 * Accessing
		 */
		shared_ptr<Column> at(int position);
		shared_ptr<Column> at(const string& name);
		shared_ptr<Column> operator[](int position);
		shared_ptr<Column> operator[](const string& name);
		shared_ptr<Column> operator[](const char* name);
		
		/*
		 * Indexing
		 */
		bool exist(const string& name);
		int position(const string& name);

		~Columns();
  };
}

#endif