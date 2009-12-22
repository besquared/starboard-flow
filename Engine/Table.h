#ifndef _table_included_
#define _table_included_

#include "Common.h"
#include "Engine/Column/Base.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;

namespace Flow {
	namespace Engine {
		class Table : vector<Column::Base> {
		public:
			Table();
			
			void push_back(const Column::Base& column);
			void push_back(const string& name, const Column::Base& column);
			void erase(const string& name);

			Column::Base& at(const size_t position);
			Column::Base& at(const string& name);

			string Inspect();
		};
	}
}

#endif