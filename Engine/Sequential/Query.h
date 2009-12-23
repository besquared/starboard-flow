/*
 *  SequenceSequenceQuery.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_sequence_query_h_
#define _flow_sequence_query_h_

#include <Common.h> 

#include "RIDList.h"
#include "RIDMap.h"
#include "RIDTree.h"

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
		
		shared_ptr< vector<string> > clusters;
		shared_ptr< vector<string> > groupings;		
		shared_ptr<Conditions> conditions;
		shared_ptr<Aggregations> aggregations;
		shared_ptr<SequenceTemplate> pattern;
		
    SequenceQuery(const string& path);
		
		/*
		 * Querying
		 */
    bool Execute(Table& result);
		
		// Materializes all tables
		bool Materialize(vector<Table>& results);
		
		// Materializes a single table
		bool Materialize(Table& results);
		
		// Materializes clustered events column
		bool Materialize(Column& column, const string& dimension, const string& alias);

		bool Merge(vector<Table>& tables, Table& results);
		bool Match(Table& results);
		bool Aggregate(Table& results);
		bool Sweep(Table& base);

		bool GatherMeasures(const set<string>& measures, Table& base);
		bool GatherDimensions(const set<string>& dimensions, Table& base);
		bool GatherEventDimension(const string& dimension, Table& base);
		
	protected:
		/*
		 * Constructing Results
		 */
		void Construct(RIDTree& tree, vector<string>& dimensions, Table& results);
    void Construct(RIDTree& tree, vector<string>& dimensions, 
									 int offset, vector<string>& values, RIDList& records, Table& results);
	};
}

#endif