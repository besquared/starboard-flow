/*
 *  Key.h
 *  flow
 *
 *  Created by Josh Ferguson on 1/2/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_analytical_key_h_
#define _flow_engine_analytical_key_h_

#include <Common.h>

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Engine {
		namespace Analytical {
			class Key {
			public:
				size_t key;
				vector<string> components;
				
				Key(const vector<string>& components);
				
				bool operator<(Key& other);
				bool operator==(Key& other);
				
				friend ostream& operator<<(ostream& out, const Key& key) {
					out << "[";
					for(size_t i = 0; i < key.components.size(); i++) {
						out << key.components[i];
						if(i < key.components.size() - 1) out << ", "; 
					}
					out << "]";
					return out;
				}
			};
		}
	}
}

#endif
