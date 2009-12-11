#ifndef _table_included_
#define _table_included_

#include "Common.h"
#include "Column.h"
#include "Columns.h"
#include "TColumn.h"
#include "TListColumn.h"

namespace Flow {
	class Columns;
	
  class Table {
  public:
    shared_ptr<Columns> columns;
		
		Table();
		
		string Inspect();
  };
}

#endif