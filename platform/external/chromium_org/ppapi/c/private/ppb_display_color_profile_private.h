/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_DISPLAY_COLOR_PROFILE_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_DISPLAY_COLOR_PROFILE_PRIVATE_H_

#include "ppapi/c/pp_array_output.h"
#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_DISPLAYCOLORPROFILE_PRIVATE_INTERFACE_0_1 \
    "PPB_DisplayColorProfile_Private;0.1"
#define PPB_DISPLAYCOLORPROFILE_PRIVATE_INTERFACE \
    PPB_DISPLAYCOLORPROFILE_PRIVATE_INTERFACE_0_1



struct PPB_DisplayColorProfile_Private_0_1 {
  PP_Resource (*Create)(PP_Instance instance);
  PP_Bool (*IsDisplayColorProfile)(PP_Resource resource);
  int32_t (*GetColorProfile)(PP_Resource display_color_profile_res,
                             struct PP_ArrayOutput color_profile,
                             struct PP_CompletionCallback callback);
  int32_t (*RegisterColorProfileChangeCallback)(
      PP_Resource display_color_profile_res,
      struct PP_CompletionCallback callback);
};

typedef struct PPB_DisplayColorProfile_Private_0_1
    PPB_DisplayColorProfile_Private;

#endif  

