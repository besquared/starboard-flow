/*
 *  Sum.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sum.h"

Aggregate::Sum::Sum(const string& measure) : Aggregate::Base::Base(measure) {}

void Aggregate::Sum::Apply(Table& base) {
	string measure = this->measures.at(0);
	
	shared_ptr< TListColumn<double> > column = 
		static_pointer_cast< TListColumn<double> >(base->columns->at(measure));
	
	shared_ptr< TColumn<double> > aggregated(new TColumn<double>);
	
	size_t column_size = column->size();
	for(size_t i = 0; i < column_size; i++) {
		vector<double> members = column->at(i);
		
		double sum = 0;
		size_t member_size = members.size();
		for(size_t j = 0; j < member_size; j++) {
			sum += members[j];
		}
		aggregated->push_back(sum);
	}
	
	shared_ptr<Column> summed = static_pointer_cast<Column>(aggregated);
	
	base.columns->push_back("sum_" + measure, summed);
}
