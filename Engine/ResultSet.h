/*
 *  ResultSet.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/6/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_engine_result_set_h_
#define _flow_engine_result_set_h_

#include <Common.h>
#include <Domain/Data/Record.h>
#include <Domain/Data/RIDList.h>

using namespace std;
using namespace Flow::Domain;

namespace Flow {
	namespace Engine {    
    class Value {
    public:
      enum ValueType { STRING, DOUBLE };

    protected:
      ValueType type;
      double dblvalue_;
      string strvalue_;

    public:
      Value(string value) {
        this->type = STRING;
        this->strvalue_ = value;
      }
      
      Value(double value) {
        this->type = DOUBLE;
        this->dblvalue_ = value;
        this->strvalue_ = boost::lexical_cast<string>(value);
      }
      
      string& to_string() {
        return strvalue_;
      }
    };
    
		class ResultSet {	
		public:
      vector<string> columns;
      vector< map<string, Value> > rows;
		};
	}
}

#endif
