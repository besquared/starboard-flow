#ifndef _column_included_
#define _column_included_

#include "Common.h"

namespace Flow {
  class Column {
	public:
		virtual string Inspect() = 0;
	};
}

#endif