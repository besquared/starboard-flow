/*
 *  ConfigurationTest.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/11/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include <Testing/TestHelper.h>
#include <Server/Configuration.h>

using namespace Flow::Server;

namespace {
	class ConfigurationTest : public ::testing::Test {
	protected:
		ConfigurationTest() {}
		virtual ~ConfigurationTest() {}
    virtual void SetUp() {}
		virtual void TearDown() {}
	};
	
	TEST_F(ConfigurationTest, ProvidesPath) {
    Configuration config("Testing/Fixture/configuration.json");
	}
}  // namespace
