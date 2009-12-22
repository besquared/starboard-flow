/*
 *  SequenceEvent.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Common.h"

namespace Flow {
	class SequenceEvent {
	public:
		RecordID record;
		string alias;
		string value;
		
		SequenceEvent(RecordID record);
		SequenceEvent(RecordID record, const string& alias);
		SequenceEvent(RecordID record, const string& alias, const string& value);
		
		bool operator<(SequenceEvent& other);
		
	private:
		friend ostream& operator<<(ostream& out, const SequenceEvent& event) {
			out << "[" + lexical_cast<string>(event.record) + ", " + event.alias + ", " + event.value + "]";
			return out;
		}
	};	
}