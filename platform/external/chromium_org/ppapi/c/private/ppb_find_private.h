/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_FIND_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_FIND_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_point.h"
#include "ppapi/c/pp_rect.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_FIND_PRIVATE_INTERFACE_0_3 "PPB_Find_Private;0.3"
#define PPB_FIND_PRIVATE_INTERFACE PPB_FIND_PRIVATE_INTERFACE_0_3



struct PPB_Find_Private_0_3 {
  void (*SetPluginToHandleFindRequests)(PP_Instance instance);
  void (*NumberOfFindResultsChanged)(PP_Instance instance,
                                     int32_t total,
                                     PP_Bool final_result);
  void (*SelectedFindResultChanged)(PP_Instance instance, int32_t index);
  void (*SetTickmarks)(PP_Instance instance,
                       const struct PP_Rect tickmarks[],
                       uint32_t count);
};

typedef struct PPB_Find_Private_0_3 PPB_Find_Private;

#endif  

