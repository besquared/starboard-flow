/*
 *  Table.h
 *  Flow
 *
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_table_h_
#define _flow_engine_table_h_

#include <Common.h>
#include <Engine/Column/Base.h>

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		class Table : vector< shared_ptr<Column::Base> > {
		public:
			Table();
			
			void push_back(const shared_ptr<Column::Base> column);
			void erase(const string& name);

			shared_ptr<Column::Base> at(const size_t position);
			shared_ptr<Column::Base> at(const string& name);
			
			size_t size() const;
			
			string Inspect();
		};
	}
}

#endif