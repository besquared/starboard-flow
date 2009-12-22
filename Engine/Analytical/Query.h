#ifndef _query_included_
#define _query_included_

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
	
  class Query {
  public:
		Measures* measures;
		ShellFragments* fragments;

		Conditions* conditions;
		vector< shared_ptr<Aggregation> >* aggregations;
		
    Query(ShellFragments* fragments, Measures* measures);
		
		/*
		 * Querying
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