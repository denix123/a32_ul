/* Copyright 2013 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_TEST_CGEN_RANGE_DEV_CHANNEL_INTERFACE_H_
#define PPAPI_C_TEST_CGEN_RANGE_DEV_CHANNEL_INTERFACE_H_

#include "ppapi/c/pp_macros.h"

#define TESTDEV_INTERFACE_1_0 "TestDev;1.0"
#define TESTDEV_INTERFACE_1_2 "TestDev;1.2"
#define TESTDEV_INTERFACE_1_3 "TestDev;1.3" 
#define TESTDEV_INTERFACE TESTDEV_INTERFACE_1_2

#define TESTDEVTOSTABLE_INTERFACE_1_0 "TestDevToStable;1.0"
#define TESTDEVTOSTABLE_INTERFACE_1_1 "TestDevToStable;1.1" 
#define TESTDEVTOSTABLE_INTERFACE_1_2 "TestDevToStable;1.2"
#define TESTDEVTOSTABLE_INTERFACE TESTDEVTOSTABLE_INTERFACE_1_2



struct TestDev_1_3 { 
  void (*TestDev1)(void);
  void (*TestDev2)(void);
  void (*TestDev3)(void);
  void (*TestDev4)(void);
};

struct TestDev_1_0 {
  void (*TestDev1)(void);
};

struct TestDev_1_2 {
  void (*TestDev1)(void);
  void (*TestDev3)(void);
};

typedef struct TestDev_1_2 TestDev;

struct TestDevToStable_1_2 {
  void (*Foo)(int32_t x);
  void (*Bar)(int32_t x);
  void (*Baz)(int32_t x);
};

typedef struct TestDevToStable_1_2 TestDevToStable;

struct TestDevToStable_1_0 {
  void (*Foo)(int32_t x);
};

struct TestDevToStable_1_1 { 
  void (*Foo)(int32_t x);
  void (*Bar)(int32_t x);
  void (*Baz)(int32_t x);
};

#endif  

