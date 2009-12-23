/*
 *  Event.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_sequential_event_h_
#define _flow_engine_sequential_event_h_

#include <Common.h>
#include <Domain/Data/Record.h>

using namespace std;
using namespace Flow;

namespace Flow {
	namespace Engine {
		namespace Sequential {
			class Event {
			public:
				RecordID record;
				string alias;
				string value;
				
				Event(RecordID record);
				Event(RecordID record, const string& alias);
				Event(RecordID record, const string& alias, const string& value);
				
				bool operator<(Event& other);
				
			private:
				friend ostream& operator<<(ostream& out, const Event& event) {
					out << "[" + boost::lexical_cast<string>(event.record) + ", " + event.alias + ", " + event.value + "]";
					return out;
				}
			};
		}
	}
}

#endif