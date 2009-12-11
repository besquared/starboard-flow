#ifndef _shell_dimensions_included_
#define _shell_dimensions_included_

#include "Common.h"
#include "ShellFragment.h"

namespace Flow {
  class ShellDimensions {
  public:
		ShellFragment *database;
  
    ShellDimensions(ShellFragment *database);
		
		// Creating and Inserting Values
		
		tuple<bool, string> Create(const string& fragment, const string& name);
		tuple<bool, string> Insert(const string& name, const string& value);
		
		// Listing and Retrieving Values
    
		vector<string> List();
    vector<string> List(const string& fragment);
    vector<string> Values(const string& dimension);
    string Fragment(const string& dimension);
		
		// Key Management
		
		string ShellDimensions::DimensionsKey();
		string ShellDimensions::DimensionsKey(const string& fragment);
		string ShellDimensions::FragmentKey(const string& name);
		string ShellDimensions::ValuesKey(const string& name);
		string ShellDimensions::ValueKey(const string& name, const string& value);
  };
}

#endif
