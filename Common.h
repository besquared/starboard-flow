#ifndef _common_included_
#define _common_included_

#include <tcutil.h>
#include <tcbdb.h>
#include <tcfdb.h>

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

#include <boost/timer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/functional/hash.hpp>
#include <boost/filesystem.hpp>

#define ok true
#define error false
#define success "Success"

#define FRAGMENT_SIZE 4

#define DEBUG

using namespace std;
using namespace boost;

namespace Flow {
	typedef double RecordID;
	
  typedef map<string, vector<RecordID> > InquiredDimension;
  typedef map<string, InquiredDimension> Inquired;
  typedef vector<RecordID> Instantiated;

	typedef tuple<bool, string> Response;
	
	namespace Common {
		vector<RecordID> Intersect(vector<RecordID> & a, vector<RecordID> & b);
		vector<string> Intersect(vector<string> & a, vector<string> & b);
		vector<string> Difference(vector<string> & a, vector<string> & b);
		
		bool IsSet(const unsigned int* set, int i);
		vector< vector<string> > PowerSet(vector<string> & values);
		
		/*
		 * Inspection
		 */
		
		string Inspect(Inquired m);
		
		template <class T>
		string Inspect(const vector<T>& v) {
			string out;
			
			out += "[";
			for(size_t i = 0; i < v.size(); i++) {
				out += boost::lexical_cast<string>(v[i]);
				if(i < v.size() - 1) out += ", "; 
			}
			out += "]";
			
			return out;
		}		
	}
}

using namespace Flow;

#endif