/*
 *  Event.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/11/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Engine/Sequential/Event.h"

using namespace Flow::Engine;

Sequential::Event::Event(RecordID record) {
	this->record = record;
}

Sequential::Event::Event(RecordID record, const string& alias) {
	this->record = record;
	this->alias = alias;
}

Sequential::Event::Event(RecordID record, const string& alias, const string& value) {
	this->record = record;
	this->alias = alias;
	this->value = value;
}

bool Sequential::Event::operator<(Event& other) {
	return this->record < other.record;
}