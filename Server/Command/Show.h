/*
 *  Show.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/11/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_server_command_show_h_
#define _flow_server_command_show_h_

#include <Common.h>

namespace Flow {
  namespace Server {
    namespace Command {
      using namespace std;
      using namespace boost;
      
      class Show {
      public:
        void databases(string& result){}
        void domains(string& database, string& result){}
      };
    }
  }
}

#endif