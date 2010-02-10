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

namespace Flow {
	namespace Engine {    
    using namespace std;
    
    class Value {
    public:
      enum ValueType { STRING, DOUBLE };

    protected:
      ValueType type;
      
      bool cast;
      double dblvalue_;
      string strvalue_;

    public:
      Value() {
        this->cast = false;
        this->type = DOUBLE;
        this->dblvalue_ = 0.0;
      }
      
      Value(const string& value) {
        this->cast = false;
        this->type = STRING;
        this->strvalue_ = value;
      }
      
      Value(const double& value) {
        this->cast = false;
        this->type = DOUBLE;
        this->dblvalue_ = value;
      }
      
      string& to_string() {
        if(type == DOUBLE && !cast) {
          cast = true;
          strvalue_ = boost::lexical_cast<string>(dblvalue_);
        }
        
        return strvalue_;
      }
      
      double& to_double() {
        if(type == STRING && !cast) {
          cast = true;
          dblvalue_ = boost::lexical_cast<double>(strvalue_);
        }
        
        return dblvalue_;
      }
      
      friend ostream& operator<<(ostream& out, Value& value) {
        out << value.to_string();
        return out;
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
