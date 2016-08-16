/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPP_FIND_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPP_FIND_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_stdint.h"

#define PPP_FIND_PRIVATE_INTERFACE_0_3 "PPP_Find_Private;0.3"
#define PPP_FIND_PRIVATE_INTERFACE PPP_FIND_PRIVATE_INTERFACE_0_3



struct PPP_Find_Private_0_3 {
  PP_Bool (*StartFind)(PP_Instance instance,
                       const char* text,
                       PP_Bool case_sensitive);
  void (*SelectFindResult)(PP_Instance instance, PP_Bool forward);
  void (*StopFind)(PP_Instance instance);
};

typedef struct PPP_Find_Private_0_3 PPP_Find_Private;

#endif  

