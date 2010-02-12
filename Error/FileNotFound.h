/*
 *  FileNotFound.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/11/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_error_file_not_found_h_
#define _flow_error_file_not_found_h_

#include <Common.h>

namespace Flow {
  namespace Error {
    using namespace std;
      
    class FileNotFound : public runtime_error {
    public:
      FileNotFound(const string& msg = "") : runtime_error(msg) {}
    };
  }
}

#endif