#ifndef _flow_common_h_
#define _flow_common_h_

#include <tcutil.h>
#include <tcbdb.h>
#include <tcfdb.h>

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

#include <boost/timer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/functional/hash.hpp>
#include <boost/filesystem.hpp>

#define DEBUG

namespace Flow {
	typedef std::map<std::string, std::string> ValueMap;
	typedef std::map< std::string, std::vector<std::string> > ValuesMap;
}

#endif