/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_IMAGE_CAPTURE_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_IMAGE_CAPTURE_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_IMAGECAPTURE_PRIVATE_INTERFACE_0_1 "PPB_ImageCapture_Private;0.1"
#define PPB_IMAGECAPTURE_PRIVATE_INTERFACE \
    PPB_IMAGECAPTURE_PRIVATE_INTERFACE_0_1



typedef void (*PPB_ImageCapture_Private_ShutterCallback)(void* user_data,
                                                         int64_t sequence_id);

typedef void (*PPB_ImageCapture_Private_PreviewCallback)(void* user_data,
                                                         int64_t sequence_id,
                                                         PP_Resource preview);

typedef void (*PPB_ImageCapture_Private_JpegCallback)(void* user_data,
                                                      int64_t sequence_id,
                                                      PP_Resource jpeg);

typedef void (*PPB_ImageCapture_Private_ErrorCallback)(void* user_data,
                                                       int64_t sequence_id,
                                                       int32_t pp_error);

struct PPB_ImageCapture_Private_0_1 {
  PP_Resource (*Create)(PP_Instance instance,
                        struct PP_Var camera_source_id,
                        PPB_ImageCapture_Private_ErrorCallback error_callback,
                        void* user_data);
  PP_Bool (*IsImageCapture)(PP_Resource resource);
  int32_t (*Close)(PP_Resource resource, struct PP_CompletionCallback callback);
  int32_t (*SetConfig)(PP_Resource image_capture,
                       PP_Resource config,
                       struct PP_CompletionCallback callback);
  int32_t (*GetConfig)(PP_Resource image_capture,
                       PP_Resource* config,
                       struct PP_CompletionCallback callback);
  int32_t (*GetCameraCapabilities)(PP_Resource image_capture,
                                   PP_Resource* capabilities,
                                   struct PP_CompletionCallback callback);
  int32_t (*CaptureStillImage)(
      PP_Resource image_capture,
      PPB_ImageCapture_Private_ShutterCallback shutter_callback,
      PPB_ImageCapture_Private_PreviewCallback preview_callback,
      PPB_ImageCapture_Private_JpegCallback jpeg_callback,
      int64_t* sequence_id);
};

typedef struct PPB_ImageCapture_Private_0_1 PPB_ImageCapture_Private;

#endif  

