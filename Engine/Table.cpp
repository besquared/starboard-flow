#include "Table.h"

Table::Table() {}

void Table::push_back(const shared_ptr<Column::Base> column) {
	vector< shared_ptr<Column::Base> >::push_back(column);
}

void Table::erase(const string& name) {}

shared_ptr<Column::Base> Table::at(const size_t position) {
	return vector< shared_ptr<Column::Base> >::at(position);
}

shared_ptr<Column::Base> Table::at(const string& name) {
	vector< shared_ptr<Column::Base> >::iterator column;
	for(column = this->begin(); column != this->end(); column++) {
		if((*column)->name == name) {
			return *column;
		}
	}
	
	return shared_ptr<Column::Base>();
}

string Table::Inspect() {
	string out;
	
	for(size_t i = 0; i < this->size(); i++) {
		out += this->at(i)->Inspect();
		if(i < this->size() - 1) out += ", "; 
	}
	
	return out;	
}