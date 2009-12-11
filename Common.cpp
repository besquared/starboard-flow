/*
 *  Utility.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Common.h"

vector<RecordID> Flow::Common::Intersect(vector<RecordID> & a, vector<RecordID> & b) {
	vector<RecordID> results;
	
	if(a.size() == 0 || b.size() == 0) return results;
	
	int aindex = 0; int bindex = 0;
	int alength = a.size(); int blength = b.size();
	
	while(aindex < alength && bindex < blength) {
		if(a[aindex] == b[bindex]) {
			results.push_back(a[aindex]);
			aindex++; bindex++;  
		} else if(a[aindex] < b[bindex]) {  
			aindex++;  
		} else {
			bindex++;  
		}
	}
	
	return results;
}

vector<string> Flow::Common::Intersect(vector<string> & a, vector<string> & b) {
	vector<string> results;
	
	if(a.size() == 0 || b.size() ==0) return results;
	
	int aindex = 0; int bindex = 0;
	int alength = a.size(); int blength = b.size();
	
	while(aindex < alength && bindex < blength) {
		string avalue = a[aindex];
		string bvalue = b[bindex];
		int comparison = avalue.compare(bvalue);
		if(comparison == 0) {
			results.push_back(avalue);
			aindex++; bindex++;  
		} else if(comparison < 0) {  
			aindex++;  
		} else {
			bindex++;  
		}
	}
	
	return results;
}

vector<string> Flow::Common::Difference(vector<string> & a, vector<string> & b) {
	vector<string> results;
	
	if(a.size() == 0 || b.size() ==0) return results;
	
	int aindex = 0; int bindex = 0;
	int alength = a.size(); int blength = b.size();
	
	while(aindex < alength && bindex < blength) {
		string avalue = a[aindex];
		string bvalue = b[bindex];
		int comparison = avalue.compare(bvalue);
		if(comparison != 0) {
			results.push_back(avalue);
			aindex++; bindex++;  
		} else if(comparison < 0) {  
			aindex++;  
		} else {
			bindex++;  
		}
	}
	
	return results;
}

vector< vector<string> > Flow::Common::PowerSet(vector<string> & values) {
	vector< vector<string> > results;
	results.push_back(vector<string>());
	
	for(unsigned int i = 1; i <= (1 << values.size()) - 1; i++) {
		vector<string> combination;
		for(int j = 0; j <= values.size() - 1; j++) {
			if(IsSet(&i, j)) { combination.push_back(values[j]); }
		}
		
		if(combination.size() > 0) { results.push_back(combination); }
	}
	
	return results;
}

bool Flow::Common::IsSet(const unsigned int *set, int i) {
	return (set[i / 32] & (1 << (i & 31)));
}

/*
 * Inspection
 */

string Flow::Common::Inspect(Inquired m) {
	string out = "{";
	
	Inquired::iterator outter = m.begin();
	Inquired::iterator outternext = m.begin(); ++outternext;
	for(outter; outter != m.end(); outter++, outternext++) {
		out += outter->first + " => {";
		InquiredDimension mi = outter->second;
		InquiredDimension::iterator inner;
		InquiredDimension::iterator innernext = mi.begin(); ++innernext;
		for(inner = mi.begin(); inner != mi.end(); inner++, innernext++) {
			out += inner->first + " => " + Inspect(inner->second);
			if(innernext != mi.end()) out += ", ";
		}
		out += "}";
		if(outternext != m.end()) out += ", ";
	}
	out += "}";
	
	return out;
}	
