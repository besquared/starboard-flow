/*
 *  Common.h
 *  Flow
 *
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_common_h_
#define _flow_common_h_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <tcutil.h>
#include <tcbdb.h>
#include <tcfdb.h>

#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/functional/hash.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#define DEBUG

namespace Flow {
	typedef std::map<std::string, std::string> ValueMap;
	typedef std::map< std::string, std::vector<std::string> > ValuesMap;
}

#endif