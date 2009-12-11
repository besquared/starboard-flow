/*
 *  Count.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Count.h"

Count::Count(const string& measure) : 
	Aggregation::Aggregation(measure) {}

void Count::Apply(shared_ptr<Table> base) {
	string measure = this->measures.at(0);
	
	// This only works on 'records' column if RecordID is a double
	shared_ptr< TListColumn<double> > column = 
	static_pointer_cast< TListColumn<double> >(base->columns->at(measure));
	
	shared_ptr< TColumn<double> > aggregated(new TColumn<double>);
	
	size_t column_size = column->size();
	for(size_t i = 0; i < column_size; i++) {
		aggregated->push_back((double)column->at(i).size());
	}
	
	shared_ptr<Column> summed = static_pointer_cast<Column>(aggregated);
	
	base->columns->push_back("count_" + measure, summed);
}
