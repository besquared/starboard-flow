/*
 *  Measure.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_measure_h_
#define _flow_measure_h_

#include "Common.h"
#include "RIDList.h"

namespace Flow {
	class Measure {
	public:
		string path;
		string name;
		TCFDB* database;
		
		Measure(string path, string name);
		~Measure();
		string Path();

		/*
		 * I/O Management
		 */
		bool Create();
		bool Close();
		bool Truncate();
		bool OpenReader();
		bool OpenWriter();
		bool Open(int mode);
		
		/*
		 * Reading
		 */
		bool Lookup(RecordID key, double& result);
		void Lookup(const RIDList& keys, vector<double>& results);
		
		/*
		 * Writing
		 */
		bool Insert(RecordID key, double value);
		
		/*
		 * Error Handling
		 */
		string Error();
	};
}

#endif