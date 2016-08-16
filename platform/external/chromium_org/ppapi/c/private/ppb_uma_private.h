/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_UMA_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_UMA_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_UMA_PRIVATE_INTERFACE_0_3 "PPB_UMA_Private;0.3"
#define PPB_UMA_PRIVATE_INTERFACE PPB_UMA_PRIVATE_INTERFACE_0_3



struct PPB_UMA_Private_0_3 {
  void (*HistogramCustomTimes)(PP_Instance instance,
                               struct PP_Var name,
                               int64_t sample,
                               int64_t min,
                               int64_t max,
                               uint32_t bucket_count);
  void (*HistogramCustomCounts)(PP_Instance instance,
                                struct PP_Var name,
                                int32_t sample,
                                int32_t min,
                                int32_t max,
                                uint32_t bucket_count);
  void (*HistogramEnumeration)(PP_Instance instance,
                               struct PP_Var name,
                               int32_t sample,
                               int32_t boundary_value);
  int32_t (*IsCrashReportingEnabled)(PP_Instance instance,
                                     struct PP_CompletionCallback callback);
};

typedef struct PPB_UMA_Private_0_3 PPB_UMA_Private;

#endif  

