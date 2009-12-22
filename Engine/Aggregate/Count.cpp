/*
 *  Count.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Count.h"

Engine::Aggregate::Count::Count(const string& measure) : 
Engine::Aggregate::Base::Base(measure) {}

void Engine::Aggregate::Count::Apply(Table& base) {
	string measure = this->measures.at(0);
	
	Column::TListColumn<double> column = 
	static_cast< Column::TListColumn<double> >(base.at(measure));
	
	Column::TColumn<double> aggregated;
	size_t column_size = column->size();
	for(size_t i = 0; i < column_size; i++) {
		aggregated->push_back((double)column->at(i).size());
	}
	base.push_back("count_" + measure, static_cast<Column::Base>(aggregated));
}
