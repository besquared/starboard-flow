/*
 *  SequenceKey.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Common.h"

namespace Flow {
	class SequenceKey {
	public:
		size_t key;
		vector<string> components;
		
		SequenceKey(const vector<string>& components);
		
		bool operator<(SequenceKey& other);
		bool operator==(SequenceKey& other);
		
		friend ostream& operator<<(ostream& out, const SequenceKey& key) {
			out << Common::Inspect(key.components);
			return out;
		}
	};
}