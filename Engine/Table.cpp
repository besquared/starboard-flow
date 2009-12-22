#include "Table.h"

Table::Table() {
	shared_ptr<Columns> columns(new Columns(this));
	
	this->columns = columns;
}

string Table::Inspect() {
	string out;
	
	for(size_t i = 0; i < this->columns->size(); i++) {
		out += this->columns->at(i)->Inspect();
		if(i < this->columns->size() - 1) out += ", "; 
	}
	
	return out;	
}