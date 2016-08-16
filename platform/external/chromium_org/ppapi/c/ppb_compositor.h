/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_COMPOSITOR_H_
#define PPAPI_C_PPB_COMPOSITOR_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_COMPOSITOR_INTERFACE_0_1 "PPB_Compositor;0.1" 


struct PPB_Compositor_0_1 { 
  PP_Bool (*IsCompositor)(PP_Resource resource);
  PP_Resource (*Create)(PP_Instance instance);
  PP_Resource (*AddLayer)(PP_Resource compositor);
  int32_t (*CommitLayers)(PP_Resource compositor,
                          struct PP_CompletionCallback cc);
  int32_t (*ResetLayers)(PP_Resource compositor);
};

#endif  

