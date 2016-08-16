/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_INPUT_EVENT_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_INPUT_EVENT_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_INPUTEVENT_PRIVATE_INTERFACE_0_1 "PPB_InputEvent_Private;0.1"
#define PPB_INPUTEVENT_PRIVATE_INTERFACE PPB_INPUTEVENT_PRIVATE_INTERFACE_0_1



struct PPB_InputEvent_Private_0_1 {
  PP_Bool (*TraceInputLatency)(PP_Resource event, PP_Bool has_damage);
  void (*StartTrackingLatency)(PP_Instance instance);
};

typedef struct PPB_InputEvent_Private_0_1 PPB_InputEvent_Private;

#endif  

