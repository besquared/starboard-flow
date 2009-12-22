#include "ShellFragments.h"

ShellFragments::ShellFragments(const string& path) {
  this->database = new ShellFragment(path);
  this->dimensions = new ShellDimensions(this->database);
}

ShellFragments::~ShellFragments() {
	delete(this->database);
  delete(this->dimensions);
}

tuple<bool, string> ShellFragments::OpenReader() {
	return this->database->OpenReader();
}

tuple<bool, string> ShellFragments::OpenWriter() {
	return this->database->OpenWriter();
}

tuple<bool, string> ShellFragments::Close() {
	return this->database->Close();
}

/*
 * Insertion
 */

tuple<bool, string> ShellFragments::Insert(RecordID record_id, const map<string, string>& row) {	
	map<string, string>::const_iterator iter;
	
	vector<string> dimensions;
	for(iter = row.begin(); iter != row.end(); iter++) {
		dimensions.push_back(iter->first);
	}

	// Allocate new fragments and dimensions
	tuple<bool, string> allocated = this->PreAllocate(dimensions);
	
	if(!allocated.get<0>()) {	
		return make_tuple(error, "Allocation failed: " + allocated.get<1>());
	}
	
	vector<string> fragments = this->List();
	for(size_t i = 0; i < fragments.size(); i++) {
		vector<string> components;
		dimensions = this->dimensions->List(fragments[i]);
		
		vector<string>::const_iterator diter;
		for(diter = dimensions.begin(); diter != dimensions.end(); diter++) {
			map<string, string>::const_iterator riter = row.find(*diter);
			
			// Insert dimension values from row
			if(riter != row.end()) {
				tuple<bool, string> inserted = 
					this->dimensions->Insert(*diter, riter->second);
				
				if(inserted.get<0>() != ok) {
					return make_tuple(error, "Insertion failed: " + inserted.get<1>());
				}
				
				components.push_back(this->Component(riter->first, riter->second));
			}
		}
		
		// Generate index keys
		vector< vector<string> > keys = Common::PowerSet(components);
		
		for(int j = 0; j < keys.size(); j++) {
			string key = this->IndexKey(fragments[i], keys[j]);
			
			tuple<bool, string> put = this->database->PutRecordID(key, record_id);
			
			if(!put.get<0>()) { return make_tuple(error, put.get<1>()); }
		}
	}
	
	return make_tuple(ok, success);
}

/*
 * Lookup
 */

vector<string> ShellFragments::List() {
  return this->database->GetList("fragments");
}

/*
 * Instantiate a dimension for a single value
 * [1, 2, 3, 4, ...]
 */
void ShellFragments::Lookup(const map<string, string>& conditions, Instantiated& results) {
  vector<string> keys;
  vector<string> fragments = this->List();

  for(size_t i = 0; i < fragments.size(); i++) {
    vector<string> values;
    vector<string> dimlist = this->dimensions->List(fragments[i]);

    for(int j = 0; j < dimlist.size(); j++) {
      map<string, string>::const_iterator condition = conditions.find(dimlist[j]);
      if(condition != conditions.end()) {
        values.push_back(this->Component(dimlist[j], condition->second));
      }
		}
    
		if(values.size() > 0) {
			keys.push_back(this->IndexKey(fragments[i], values));
		}
  }
	
	results = this->database->GetRecordIdList(keys);
}

/*
 * Inquire a set of values from a dimension
 * {'A' => {'a' => ['1', '2'], 'b' => ['3', 4']}}
 */
void ShellFragments::Lookup(const vector<string>& dimensions, Inquired& results) {
	Conditions conditions;
	this->Lookup(dimensions, conditions, results);
}

void ShellFragments::Lookup(const vector<string>& dimensions, Conditions& conditions, Inquired& results) {
	for(size_t i = 0; i < dimensions.size(); i++) {
    InquiredDimension dimension;
    
    string fragment = this->dimensions->Fragment(dimensions[i]);
    vector<string> values = this->dimensions->Values(dimensions[i]);
		
		sort(values.begin(), values.end());
		
		conditions.Apply(dimensions[i], values);
		// Run values through a set of conditional filters here
		
    for(int j = 0; j < values.size(); j++) {
      dimension[values[j]] = this->database->GetRecordIdList(
				this->IndexKey(fragment, this->Component(dimensions[i], values[j]))
			);
    }
    
    results[dimensions[i]] = dimension;
  }	
}

/*
 * Combine inquired and instantiated dimensions together
 * {'A' => {'a' => ['1', '2'], 'b' => ['3', 4']}, 'C' => {'c' => 1, 2, 3, 4, ...}}
 */
void ShellFragments::Lookup(const map<string, string>& instantiate, const vector<string>& dimensions, Inquired& results) {
	Conditions conditions;
	this->Lookup(instantiate, dimensions, conditions, results);
}

void ShellFragments::Lookup(const map<string, string>& instantiate, const vector<string>& dimensions, Conditions& conditions, Inquired& results) {
	Instantiated instantiated;

	this->Lookup(dimensions, conditions, results);
	this->Lookup(instantiate, instantiated);

	if(instantiated.size() > 0) {
		map<string, string>::const_iterator instance;
		
		InquiredDimension dimension;
		for(instance = instantiate.begin(); instance != instantiate.end(); instance++) {
			dimension.clear();
			dimension[instance->second] = instantiated;
			results[instance->first] = dimension;
		}
	}
}

/*
 * Creation and Allocation
 */

tuple<bool, string, int> ShellFragments::Create() {
	tuple<bool, string, int> added = this->database->AddInt("last_fragment_id", 1);
	
	if(added.get<0>()) {
		string stringified = lexical_cast<string>(added.get<2>());
		tuple<bool, string> written = this->database->PutDup("fragments", stringified);
		
		if(written.get<0>()) {
			return added;
		} else {
			return make_tuple(error, written.get<1>(), INT_MIN);
		}
	} else {
		return added;
	}
}


tuple<bool, string> ShellFragments::PreAllocate(const vector<string>& record_dims) {
	vector<string> dimensions = this->dimensions->List();
	
	for(size_t i = 0; i < record_dims.size(); i++) {
		vector<string>::iterator iter;
		iter = find(dimensions.begin(), dimensions.end(), record_dims[i]);
		
		if(iter == dimensions.end()) {
			string last_fragment;
			vector<string> fragments = this->List();
			
			if(fragments.empty()) {
				last_fragment = "0";
			} else {
				last_fragment = fragments[fragments.size() - 1];
			}
			
			vector<string> fragment_dims = this->dimensions->List(last_fragment);
			if(fragment_dims.size() == 0 || fragment_dims.size() == FRAGMENT_SIZE) {
				tuple<bool, string, int> frag_created = this->Create();

				if(frag_created.get<0>()) {
					last_fragment = boost::lexical_cast<string>(frag_created.get<2>());
				} else {
					return make_tuple(error, "Allocation failed: " + frag_created.get<1>());
				}
			}
			
			tuple<bool, string> dim_created =
				this->dimensions->Create(last_fragment, record_dims[i]);
			
			if(!dim_created.get<0>()) {
				return make_tuple(error, "Allocation failed: " + dim_created.get<1>());
			}
		}
	}
	
	return make_tuple(ok, success);
}

/*
 * Key Management
 */

string ShellFragments::Component(const string& dimension, const string& value) {
	return dimension + "[" + value + "]";
}

string ShellFragments::IndexKey(const string& fragment, const string& component) {
	return fragment + ":<" + component + ">";
}

string ShellFragments::IndexKey(const string& fragment, const vector<string>& components) {
	return fragment + ":<" + boost::join(components, ":") + ">";
}