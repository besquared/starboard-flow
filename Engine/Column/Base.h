#ifndef _flow_engine_column_base_included_
#define _flow_engine_column_base_included_

#include "Common.h"

using namespace std;
using namespace boost;

namespace Flow {
	namespace Engine {
		namespace Column {
			class Base {
			public:
				string name;
				virtual string Inspect() = 0;
			};
		}
	}
}

#endif