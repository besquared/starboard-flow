/*
 *  flow_driver.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "flow_driver.h"

DRIVER_INIT(basic_driver) {
  return &basic_driver_entry;
}

static ErlDrvData start(ErlDrvPort port, char* cmd) {
  basic_drv_t* retval = (basic_drv_t*) driver_alloc(sizeof(basic_drv_t));
  retval->port = port;
  return (ErlDrvData) retval;
}

static void stop(ErlDrvData handle) {
  basic_drv_t* driver_data = (basic_drv_t*) handle;
  driver_free(driver_data);
}

static void process(ErlDrvData handle, ErlIOVec *ev) {
  basic_drv_t* driver_data = (basic_drv_t*) handle;
  ErlDrvBinary* data = ev->binv[1];
  ErlDrvTermData spec[] = {ERL_DRV_ATOM, driver_mk_atom("ok"),
		ERL_DRV_BINARY, (ErlDrvTermData) data, data->orig_size, 0,
	ERL_DRV_TUPLE, 2};
  driver_output_term(driver_data->port, spec, sizeof(spec) / sizeof(spec[0]));
}