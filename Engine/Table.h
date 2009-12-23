#ifndef _table_included_
#define _table_included_

#include <Common.h>
#include "Engine/Column/Base.h"

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

			string Inspect();
		};
	}
}

#endif