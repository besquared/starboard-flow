#include "Table.h"

Engine::Table::Table() {}

void Engine::Table::erase(const string& name) {}

Column::Base& Engine::Table::at(const string& name) {
	vector<Column::Base>::iterator column;
	for(column = this->begin(); column != this->end(); column++) {
		if(column->name == name) {
			return *column;
		}
	}
}

string Engine::Table::Inspect() {
	string out;
	
	for(size_t i = 0; i < this->size(); i++) {
		out += this->at(i).Inspect();
		if(i < this->size() - 1) out += ", "; 
	}
	
	return out;	
}