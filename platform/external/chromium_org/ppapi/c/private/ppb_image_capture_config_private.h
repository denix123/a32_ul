/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_IMAGE_CAPTURE_CONFIG_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_IMAGE_CAPTURE_CONFIG_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_IMAGECAPTURECONFIG_PRIVATE_INTERFACE_0_1 \
    "PPB_ImageCaptureConfig_Private;0.1"
#define PPB_IMAGECAPTURECONFIG_PRIVATE_INTERFACE \
    PPB_IMAGECAPTURECONFIG_PRIVATE_INTERFACE_0_1



struct PPB_ImageCaptureConfig_Private_0_1 {
  PP_Resource (*Create)(PP_Instance instance);
  PP_Bool (*IsImageCaptureConfig)(PP_Resource resource);
  void (*GetPreviewSize)(PP_Resource config, struct PP_Size* preview_size);
  void (*SetPreviewSize)(PP_Resource config,
                         const struct PP_Size* preview_size);
  void (*GetJpegSize)(PP_Resource config, struct PP_Size* jpeg_size);
  void (*SetJpegSize)(PP_Resource config, const struct PP_Size* jpeg_size);
};

typedef struct PPB_ImageCaptureConfig_Private_0_1
    PPB_ImageCaptureConfig_Private;

#endif  

