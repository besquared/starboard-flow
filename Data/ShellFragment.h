#ifndef _shell_fragment_included_
#define _shell_fragment_included_

#include "Common.h"

namespace Flow {
	class ShellFragment {
	public:
		string path;
		TCBDB *database;
		bool opened;
		bool writer;
	
		ShellFragment(const string& path);
		tuple<bool, string> Create();
		tuple<bool, string> OpenReader();
		tuple<bool, string> OpenWriter();
		tuple<bool, string> Open(bool writer);
		tuple<bool, string> Close();
		tuple<bool, string> Truncate();
		string Path();
	
		/*
		 * Reading
		 */
		
		string Get(const string& key);
		int GetInt(const string& key);
		double GetDouble(const string& key);
		char * GetRaw(const string& key);
		vector<string> GetList(const string& key);
		TCLIST * GetListRaw(const string& key);
		
		vector<RecordID> GetRecordIdList(const string& key);
		vector<RecordID> GetRecordIdList(const vector<string>& keys);
		
		/*
		 * Writing
		 */
		
		tuple<bool, string> Put(const string& key, const string& value);
		tuple<bool, string> PutDup(const string& key, const string& value);
		tuple<bool, string> PutList(const string& key, const vector<string>& values);
		tuple<bool, string> PutRecordID(const string& key, RecordID value);

		tuple<bool, string, int> AddInt(const string& key, int value);
		tuple<bool, string, double> AddDouble(const string& key, double value);
		
		/*
		 * Transactions
		 */
		tuple<bool, string> TransactionBegin();
		tuple<bool, string> TransactionAbort();
		tuple<bool, string> TransactionCommit();
		
		/*
		 * Keys
		 */
		vector<string> Keys();
		vector<string> Keys(const string& prefix);
		vector<string> Keys(const string& prefix, int max);
		
		/*
		 * Errors
		 */
		string Error();
		
		~ShellFragment();

		/*
		 * Data Conversion
		 */
		
		string Intern(char* element);
		int ShellFragment::InternInt(char *element);
		double ShellFragment::InternDouble(char *element);
		vector<string> InternList(TCLIST *list);
		vector<RecordID> InternRecordIdList(TCLIST *list);
		
		/*
		 * Intersection
		 */
		
		TCLIST* IntersectRecordIdLists(TCLIST *a, TCLIST *b);
	};
}

#endif