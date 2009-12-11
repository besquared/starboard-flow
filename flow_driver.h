/*
 *  flow_driver.h
 *  Flow
 *
 *  Created by Josh Ferguson on 11/29/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include <erl_driver.h>
#include <ei.h>

typedef struct _basic_drv_t {
  ErlDrvPort port;
} basic_drv_t;


static ErlDrvData start(ErlDrvPort port, char* cmd);
static void stop(ErlDrvData handle);
static void process(ErlDrvData handle, ErlIOVec *ev);

static ErlDrvEntry basic_driver_entry = {
NULL,                             /* init */
start,                            /* startup */
stop,                             /* shutdown */
NULL,                             /* output */
NULL,                             /* ready_input */
NULL,                             /* ready_output */
"basic_drv",                        /* the name of the driver */
NULL,                             /* finish */
NULL,                             /* handle */
NULL,                             /* control */
NULL,                             /* timeout */
process,                          /* process */
NULL,                             /* ready_async */
NULL,                             /* flush */
NULL,                             /* call */
NULL,                             /* event */
ERL_DRV_EXTENDED_MARKER,          /* ERL_DRV_EXTENDED_MARKER */
ERL_DRV_EXTENDED_MAJOR_VERSION,   /* ERL_DRV_EXTENDED_MAJOR_VERSION */
ERL_DRV_EXTENDED_MAJOR_VERSION,   /* ERL_DRV_EXTENDED_MINOR_VERSION */
ERL_DRV_FLAG_USE_PORT_LOCKING     /* ERL_DRV_FLAGs */
};
