/*
 *  SequenceEvent.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "SequenceEvent.h"

SequenceEvent::SequenceEvent(RecordID record) {
	this->record = record;
}

SequenceEvent::SequenceEvent(RecordID record, const string& alias) {
	this->record = record;
	this->alias = alias;
}

SequenceEvent::SequenceEvent(RecordID record, const string& alias, const string& value) {
	this->record = record;
	this->alias = alias;
	this->value = value;
}

bool SequenceEvent::operator<(SequenceEvent& other) {
	return this->record < other.record;
}