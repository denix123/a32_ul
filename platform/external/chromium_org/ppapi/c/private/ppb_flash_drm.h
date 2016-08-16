/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_FLASH_DRM_H_
#define PPAPI_C_PRIVATE_PPB_FLASH_DRM_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_FLASH_DRM_INTERFACE_1_0 "PPB_Flash_DRM;1.0"
#define PPB_FLASH_DRM_INTERFACE_1_1 "PPB_Flash_DRM;1.1"
#define PPB_FLASH_DRM_INTERFACE PPB_FLASH_DRM_INTERFACE_1_1



struct PPB_Flash_DRM_1_1 {
  PP_Resource (*Create)(PP_Instance instance);
  int32_t (*GetDeviceID)(PP_Resource drm,
                         struct PP_Var* id,
                         struct PP_CompletionCallback callback);
  PP_Bool (*GetHmonitor)(PP_Resource drm, int64_t* hmonitor);
  int32_t (*GetVoucherFile)(PP_Resource drm,
                            PP_Resource* file_ref,
                            struct PP_CompletionCallback callback);
  int32_t (*MonitorIsExternal)(PP_Resource drm,
                               PP_Bool* is_external,
                               struct PP_CompletionCallback callback);
};

typedef struct PPB_Flash_DRM_1_1 PPB_Flash_DRM;

struct PPB_Flash_DRM_1_0 {
  PP_Resource (*Create)(PP_Instance instance);
  int32_t (*GetDeviceID)(PP_Resource drm,
                         struct PP_Var* id,
                         struct PP_CompletionCallback callback);
  PP_Bool (*GetHmonitor)(PP_Resource drm, int64_t* hmonitor);
  int32_t (*GetVoucherFile)(PP_Resource drm,
                            PP_Resource* file_ref,
                            struct PP_CompletionCallback callback);
};

#endif  
