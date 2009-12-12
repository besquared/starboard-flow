/*
 *  SequenceSequenceQuery.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _sequence_query_included_
#define _sequence_query_included_

#include "Common.h"
#include "Measure.h"
#include "Measures.h"
#include "Dimension.h"
#include "Dimensions.h"
#include "ShellFragment.h"
#include "ShellFragments.h"

#include "Table.h"
#include "Conditions.h"
#include "Aggregations.h"
#include "SequenceTemplate.h"
#include "SequenceKey.h"
#include "SequenceEvent.h"

namespace Flow {
	class Conditions;
	
  class SequenceQuery {
  public:
		shared_ptr<Measures> measures;
		shared_ptr<Dimensions> dimensions;
		shared_ptr<ShellFragments> fragments;
		
		vector<string> clusters;
		vector<string> groupings;		
		shared_ptr<Conditions> conditions;
		shared_ptr<Aggregations> aggregations;
		shared_ptr<SequenceTemplate> pattern;
		
    SequenceQuery(const string& path);
		
		/*
		 * Querying
		 */
    tuple< bool, string, shared_ptr<Table> > Execute();
		Response Materialize(vector< shared_ptr<Table> >& results);
		Response Materialize(shared_ptr<Table> results);
		Response Merge(vector< shared_ptr<Table> >& tables, shared_ptr<Table> results);
		Response Match(shared_ptr<Table> results);
		Response Aggregate(shared_ptr<Table> results);
		Response Sweep(shared_ptr<Table> base);

		Response GatherMeasure(const string& measure, shared_ptr<Table> base);
		Response GatherMeasure(const string& measure, const string& alias, shared_ptr<Table> base);
		Response GatherMeasures(const set<string>& measures, shared_ptr<Table> base);
		
		Response GatherDimension(const string& dimension, shared_ptr<Table> base);
		Response GatherDimension(const string& dimension, const string& alias, shared_ptr<Table> base);
		Response GatherDimensions(const set<string>& dimensions, shared_ptr<Table> base);

	protected:
		/*
		 * Constructing Results
		 */
		void Construct(Inquired & inquired, vector<string> & dimensions, shared_ptr<Table> results);
    void Construct(Inquired & inquired, vector<string> & dimensions, 
									 int offset, vector<string> & values, vector<RecordID> & records, shared_ptr<Table> results);
	};
}

#endif