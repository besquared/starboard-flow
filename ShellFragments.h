#ifndef _shell_fragments_included_
#define _shell_fragments_included_

#include "Common.h"

#include "ShellDimensions.h"
#include "ShellFragment.h"

#include "Conditions.h"

#define FRAGMENT_SIZE 4

namespace Flow {
  class ShellFragments {
  public:
		ShellFragment *database;
    ShellDimensions *dimensions;
  
    ShellFragments(const string& path);
		
		// Opening/Closing
		tuple<bool, string> OpenReader();
		tuple<bool, string> OpenWriter();
		tuple<bool, string> Close();
		
		// Insertion
		
		tuple<bool, string> Insert(RecordID record_id, const map<string, string>& row);
		
		// Lookup
		
    vector<string> List();
		
		// Instantiate a single dimension
		void Lookup(const map<string, string>& conditions, Instantiated& results);
		
		// Inquire a set of values for a dimension
		void Lookup(const vector<string>& dimensions, Inquired& results);
		void Lookup(const vector<string>& dimensions, Conditions& conditions, Inquired& results);

		// Instantiate and inquire dimensions
		void Lookup(const map<string, string>& instantiate, const vector<string>& dimensions, Inquired& results);
		void Lookup(const map<string, string>& instantiate, const vector<string>& dimensions, Conditions& conditions, Inquired& results);		
		vector<RecordID> Intersect(const vector<RecordID>& a, const vector<RecordID>& b);
		vector<string> Intersect(const vector<string>& a, const vector<string>& b);
		
    ~ShellFragments();
		
		// Creation and Allocation
		
		tuple<bool, string, int> Create();
		tuple<bool, string> PreAllocate(const vector<string>& dimensions);
		
		// Key Management
		
		string Component(const string& dimension, const string& value);
		string IndexKey(const string& fragment, const string& component);
		string IndexKey(const string& fragment, const vector<string>& components);
		
		// Utilities
		
		vector< vector<string> > PowerSet(const vector<string>& values);
		bool IsSet(const unsigned int *set, int i);		
  };
}

#endif