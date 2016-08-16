/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_CAMERA_CAPABILITIES_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_CAMERA_CAPABILITIES_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_CAMERACAPABILITIES_PRIVATE_INTERFACE_0_1 \
    "PPB_CameraCapabilities_Private;0.1"
#define PPB_CAMERACAPABILITIES_PRIVATE_INTERFACE \
    PPB_CAMERACAPABILITIES_PRIVATE_INTERFACE_0_1



struct PPB_CameraCapabilities_Private_0_1 {
  PP_Resource (*Create)(PP_Instance instance);
  PP_Bool (*IsCameraCapabilities)(PP_Resource resource);
  void (*GetSupportedPreviewSizes)(PP_Resource capabilities,
                                   int32_t* array_size,
                                   struct PP_Size** preview_sizes);
  void (*GetSupportedJpegSizes)(PP_Resource capabilities,
                                int32_t* array_size,
                                struct PP_Size** jpeg_sizes);
};

typedef struct PPB_CameraCapabilities_Private_0_1
    PPB_CameraCapabilities_Private;

#endif  

