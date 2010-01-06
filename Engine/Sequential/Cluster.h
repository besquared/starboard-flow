/*
 *  Cluster.h
 *  Flow
 *
 *  Created by Josh Ferguson on 1/5/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_cluster_h_
#define _flow_engine_sequential_cluster_h_

#include <Common.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>

using namespace std;
using namespace Flow;
using namespace Flow::Domain;

namespace Flow {
	namespace Engine {
		namespace Sequential {
			class Cluster : public vector<RecordID> {
			public:
				vector<string> table;
				vector<string> dimensions;
				
				Cluster(const vector<string>& dimensions);  
				void Insert(double record, vector<string>& values);  
				
				template <typename input_iterator>
				void Insert(double record, input_iterator first, input_iterator last) {
					this->push_back(record);
					copy(first, last, back_inserter(this->table));
				}
					
			private:
				friend ostream& operator<<(ostream& out, const Cluster& cluster) {
					size_t i;
					
					out << "[";
					for(i = 0; i < cluster.size(); i++) {
						out << cluster[i];
						if(i < cluster.size() - 1) out << ", "; 
					}
					out << "]\n";
					
					out << "[";
					for(i = 0; i < cluster.table.size(); i++) {
						if(i % cluster.dimensions.size() == 0) out << "[";
						
						out << cluster.table[i];
						
						if((i + 1) % cluster.dimensions.size() == 0) {
							out << "], ";
						} if(i < cluster.table.size() - 1) {
							out << ", ";
						}
					}
					out << "]";
					
					return out;
				}
			};
		}
	}
}

#endif