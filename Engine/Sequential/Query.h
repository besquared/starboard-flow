/*
 *  Query.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_query_h_
#define _flow_engine_sequential_query_h_

#include <Common.h> 
#include <Conditions.h>
#include <Domain/Base.h>
#include <Engine/Table.h>
#include <Engine/Aggregates.h>

#include "Key.h"
#include "Event.h"
#include "Pattern.h"

using namespace std;
using namespace Flow;
using namespace Flow::Engine;
using namespace Flow::Domain;
using namespace Flow::Domain::Data;

namespace Flow {
	namespace Engine {
		namespace Sequential {
			class Query {
			public:
				Domain::Base* domain;
				
				vector<string> clusters;
				vector<string> groupings;		
				Conditions conditions;
				Aggregates aggregates;
				Pattern pattern;
				
				Query(const string& path);
				
				/*
				 * Querying
				 */
				bool Execute(Table& result);
				
				// Materializes all tables
				bool Materialize(vector<Table>& results);
				
				// Materializes a single table
				bool Materialize(Table& results);
				
				// Materializes clustered events column
				bool Materialize(Column::Base& column, const string& dimension, const string& alias);

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
	}
}

#endif