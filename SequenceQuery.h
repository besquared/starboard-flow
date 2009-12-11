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
#include "Aggregation.h"

namespace Flow {
	class Conditions;
	
  class SequenceQuery {
  public:
		shared_ptr<Measures> measures;
		shared_ptr<Dimensions> dimensions;
		shared_ptr<ShellFragments> fragments;
		shared_ptr<Conditions> conditions;
		vector< shared_ptr<Aggregation> > aggregations;

		vector<string> clusters;
		vector<string> groupings;
		
    SequenceQuery(const string& path);
		
		/*
		 * SequenceQuerying
		 */
    tuple< bool, string, shared_ptr<Table> > Execute();
		Response Materialize(shared_ptr<Table> results);
		Response Aggregate(shared_ptr<Table> results);
		Response Gather(const set<string>& measures, shared_ptr<Table> base);
		Response Sweep(shared_ptr<Table> base);
		
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