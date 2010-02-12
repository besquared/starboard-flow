/*
 *  Parser.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/11/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#ifndef _flow_server_command_parser_h_
#define _flow_server_command_parser_h_

#include <Common.h>
#include <Library/jsonxx/jsonxx.h>

namespace Flow {
  namespace Server {
    namespace Command {
      using namespace std;
      
      class Parser {
      public:
        void parse(string& command);
      };
    }
  }
}

#endif