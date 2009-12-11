#include <tcutil.h>
#include <tcbdb.h>

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <set>
#include <map>
#include <vector>
#include <iostream>

#include <boost/timer.hpp>
#include <boost/algorithm/string.hpp>

#include <gtest/gtest.h>

#include "Flow.h"

using namespace std;
using namespace Flow;

int main(int argc, char **argv){	
	::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
