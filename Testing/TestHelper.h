/*
 *  TestHelper.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_testing_test_helper_h_
#define _flow_testing_test_helper_h_

#include <Common.h>
#include <Domain/Base.h>
#include <Engine/Query/Analytical.h>
#include <Engine/Query/Sequential.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::_;

using namespace Flow;

#endif
