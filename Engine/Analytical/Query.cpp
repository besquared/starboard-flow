/*
 *  Query.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

/*
 * A query takes a measure and a set of conditions in the form of
 *  {"A" => "a1", "B" => "?", "C" => "*"}
 *
 * and returns a set of column vectors that contains the appropriate answers, 
 * for instance a query like 
 * 
 * {"Product" => "P1", "Store" => "?" : SUM(SALE), COUNT(SALE)} 
 *
 * might return
 *
 * [ [S1, S2, S3], [10.5, 10.8, 10.2], [2, 2, 2] ]
 */

#include "Query.h"

Analytical::Query::Query(Domain::Base* domain) {
	this->domain = domain;
	this->conditions = new Conditions();
	this->aggregates = new Aggregates();
}

bool Analytical::Query::Execute(Groups& results) {	
	if(!this->Materialize(results)) { return false; }
	if(!this->Aggregate(results)) { return false; }
	if(!this->Sweep(results)) { return false; }
	return true;
}

bool Analytical::Query::Materialize(Groups& results) {
	set<string> inquire;
	vector<string> dimensions;
	map<string, string> instantiate;
	Conditions inquiry_conditions;
	
	for(size_t i = 0; i < this->conditions->size(); i++) {
		shared_ptr<Condition::Base> condition = this->conditions->at(i);
		
		if(condition->type == Condition::Base::EQ) {
			shared_ptr<Condition::Eq> equals = static_pointer_cast<Condition::Eq>(condition);
			
			if(equals->value == "?") {
				inquire.insert(condition->column);
			} else {
				instantiate[condition->column] = equals->value;
			}			
		} else {
			inquiry_conditions.push_back(condition);
		}
		
		dimensions.push_back(condition->column);
	}

	RIDList instantiated;
	if(instantiate.size() > 0) {
		this->domain->indices->Lookup(instantiate, instantiated);
		if(instantiated.size() == 0) return true;
	}
	
	if(inquire.size() > 0) {
		RIDTree inquired;
		this->domain->indices->Lookup(inquire, inquiry_conditions, inquired);
		
		if(inquired.size() == 0) {
			return true;
		} else {
			this->Construct(instantiated, inquired, dimensions, results);
		}
	} else {
		if(instantiated.size() > 0) {
			// just insert the instantiated ids into groups
		}
	}
	
	return true;
}

bool Analytical::Query::Aggregate(Groups& base) {
	// go through all the aggregations and gather
	//   their measures from disk if we don't have them
	
//	size_t size = this->aggregates->size();
//	
//	set<string> measures;
//	for(size_t i = 0; i < size; i++) {
//		vector<string> ameasures = this->aggregates->at(i)->measures;
//		measures.insert(ameasures.begin(), ameasures.end());
//	}
//	
//	if(this->Gather(measures, base)) {
//		for(size_t j = 0; j < size; j++) {
//			this->aggregates->at(j)->Apply(base);	
//		}
//		return true;
//	} else {
//		return false;
//	}
	return true;
}

bool Analytical::Query::Sweep(Groups& base) {
	// go through and drop the columns that 
	//  we don't want returned (records and measures)
	
//	size_t size = this->aggregates->size();
//	
//	set<string> measures;
//	for(size_t i = 0; i < size; i++) {
//		vector<string> ameasures = this->aggregates->at(i)->measures;
//		measures.insert(ameasures.begin(), ameasures.end());
//	}
//	measures.insert("records");
//	
//	set<string>::iterator measure;
//	for(measure = measures.begin(); measure != measures.end(); measure++) {
//		base.erase(*measure);
//	}
//	
	return true;
}

// Gather all the measures needed by the aggregates
bool Analytical::Query::Gather(const set<string>& measures, Groups& base) {
//	set<string>::const_iterator measure;
//	for(measure = measures.begin(); measure != measures.end(); measure++) {		
//		shared_ptr< Column::TListColumn<double> > values(new Column::TListColumn<double>(*measure));
//		
//		shared_ptr< Column::TColumn<RIDList> > records = 
//		static_pointer_cast< Column::TColumn<RIDList> >(base.at("records"));
//		
//		vector<double> mvalues;
//		for(size_t i = 0; i < records->size(); i++) {
//			mvalues.clear();
//			this->domain->measures->Lookup(*measure, records->at(i), mvalues);
//			values->push_back(mvalues);
//		}			
//		base.push_back(static_pointer_cast<Column::Base>(values));
//	}
	
	return true;
}

/*
 * Construction
 */
void Analytical::Query::Construct(RIDList& instantiated, RIDTree& inquired, vector<string>& dimensions, Groups& results) {
	RIDList records;
	vector<string> values;
	this->Construct(instantiated, inquired, dimensions, 0, values, records, results);
}

/*
 Takes a set of inquired dimensions such as:
	{A => {a1 => [1, 2, 3]}, B => {b1 => [1, 2], b2 => [3]}}
 
 and builds a table with dimension values corresponding record list
 +----+-----+--------+
 | values   | id     |
 |----------|--------|
 | [a1, b1] | [1, 2] |
 | [a1, b2] | [3]    |
 +----------+--------|
 
 values holds the list of dimension values, ie: a1, b1
 records hold the list of records for those values, ie: [1, 2]
 
 We do this by a depth first search, building nodes as we traverse
 down "branches". First we start with A:a1, descend into B and intersect
 list A:a1 with B:b1, if there are any members of this new list, we descend
 again and the termination condition triggers and we copy the values list
 and the id list into the table and return. We continue by searching B:b2
 and so on.
*/
void Analytical::Query::Construct(RIDList& instantiated, RIDTree& inquired, vector<string>& dimensions, 
																	int offset, vector<string>& values, RIDList& records, Groups& results) {
	
	if(dimensions.size() == offset) {
		RIDList intersected = records & instantiated;
		
		if(intersected.size() > 0) {
			Group group(values);
			results.push_back(group);
			copy(results.back().begin(), results.back().end(), back_inserter(results.back()));
		}
		return;
	}
	
	RIDMap::iterator rpair;
	RIDMap rmap = inquired[dimensions[offset]];
	for(rpair = rmap.begin(); rpair != rmap.end(); rpair++) {
		RIDList intersection = 
			(records.empty() ? rpair->second : records & rpair->second);
		
		if(intersection.size() > 0) {
			values.push_back(rpair->first);
			this->Construct(instantiated, inquired, dimensions, 
											offset + 1, values, intersection, results);
			values.pop_back();
		}
	}
}