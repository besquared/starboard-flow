/*
 *  Configuration.cpp
 *  flow
 *
 *  Created by Josh Ferguson on 2/11/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Configuration.h"

Flow::Server::Configuration::Configuration(const string& path) {
  ifstream input(path.c_str());
  
  if(!input.is_open()) {
    throw Error::FileNotFound("Could not find configuration file " + path);
  }

  jsonxx::Object config;
  jsonxx::Object::parse(input, config);

  input.close();
  
//  istringstream input(teststr);
//  Object o;
//  assert(Object::parse(input, o));
//  assert(1 == o.get<double>("foo"));
//  assert(o.has<bool>("bar"));
//  assert(o.has<Object>("person"));
//  assert(o.get<Object>("person").has<double>("age"));
//  assert(o.has<Array>("data"));
//  assert(o.get<Array>("data").get<double>(1) == 42);
//  assert(o.get<Array>("data").get<string>(0) == "abcd");
//  assert(o.get<Array>("data").get<double>(2) == 54.7);
//  assert(!o.has<double>("data"));  
}