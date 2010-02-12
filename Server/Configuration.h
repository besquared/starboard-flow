/*
 *  Configuration.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/11/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#ifndef _flow_server_congifuration_h_
#define _flow_server_congifuration_h_

#include <Common.h>
#include <Library/jsonxx/jsonxx.h>

namespace Flow {
  namespace Server {
    using namespace std;

    class Configuration {
    public:
      Configuration(const string& path);
    };
  }
}

#endif