/*
 *  TestHelper.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _test_helper_included_
#define _test_helper_included_

#include "Flow.h"
#include <gtest/gtest.h>

using namespace Flow;

class TestHelper {
public:
	string Inspect(vector<string> v) {
		string out;
		
		out += "[";
		for(size_t i = 0; i < v.size(); i++) {
			out += v[i];
			if(i < v.size() - 1) out += ", "; 
		}
		out += "]";
		
		return out;
	}
	
	string Inspect(vector<RecordID> v) {
		string out;
		
		out += "[";
		for(size_t i = 0; i < v.size(); i++) {
			out += lexical_cast<string>(v[i]);
			if(i < v.size() - 1) out += ", "; 
		}
		out += "]";
		
		return out;
	}
	
	string Inspect(vector< vector<string> > v) {
		string out;
		
		out += "[";
		for(size_t i = 0; i < v.size(); i++) {
			out += this->Inspect(v[i]);
			if(i < v.size() - 1) out += ", "; 
		}
		out += "]";
		
		return out;
	}	
		
	string Inspect(Inquired m) {
		string out = "{";
		
		Inquired::iterator outter = m.begin();
		Inquired::iterator outternext = m.begin(); ++outternext;
		for(outter; outter != m.end(); outter++, outternext++) {
			out += outter->first + " => {";
			InquiredDimension mi = outter->second;
			InquiredDimension::iterator inner;
			InquiredDimension::iterator innernext = mi.begin(); ++innernext;
			for(inner = mi.begin(); inner != mi.end(); inner++, innernext++) {
				out += inner->first + " => " + this->Inspect(inner->second);
				if(innernext != mi.end()) out += ", ";
			}
			out += "}";
			if(outternext != m.end()) out += ", ";
		}
		out += "}";
		
		return out;
	}	
};

#endif
