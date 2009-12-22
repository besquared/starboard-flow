/*
 *  Count.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Count.h"

Aggregate::Count::Count(const string& measure) : 
Aggregate::Base::Base(measure) {}

void Aggregate::Count::Apply(Table& base) {
	string measure = this->measures.at(0);
	
	shared_ptr< Column::TListColumn<double> > column = 
	static_pointer_cast< Column::TListColumn<double> >(base.at(measure));
	
	shared_ptr< Column::TColumn<double> > aggregated(new Column::TColumn<double>("count_" + measure));
	
	size_t column_size = column->size();
	for(size_t i = 0; i < column_size; i++) {
		aggregated->push_back((double)column->at(i).size());
	}
	base.push_back(aggregated);
}
