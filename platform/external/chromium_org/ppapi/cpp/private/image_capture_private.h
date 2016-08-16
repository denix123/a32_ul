/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef PPAPI_CPP_PRIVATE_IMAGE_CAPTURE_PRIVATE_H_
#define PPAPI_CPP_PRIVATE_IMAGE_CAPTURE_PRIVATE_H_

#include "ppapi/c/private/ppb_image_capture_private.h"
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/private/camera_capabilities_private.h"
#include "ppapi/cpp/private/image_capture_config_private.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/var.h"

namespace pp {

class ImageCapture_Private {
 public:
  
  
  ImageCapture_Private();

  
  
  
  
  
  
  
  
  
  
  
  
  
  ImageCapture_Private(const InstanceHandle& instance,
                       const Var& camera_source_id,
                       PPB_ImageCapture_Private_ErrorCallback error_callback,
                       void* user_data);

  
  
  
  
  
  explicit ImageCapture_Private(const Resource& resource);

  
  
  
  
  
  ImageCapture_Private(PassRef, PP_Resource resource);

  
  ~ImageCapture_Private();

  
  
  
  
  
  
  
  
  
  
  int32_t Close(const CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  
  
  int32_t SetConfig(const ImageCaptureConfig_Private& config,
                    const CompletionCallback& callback);

  
  
  
  
  
  
  int32_t GetConfig(
      const CompletionCallbackWithOutput<ImageCaptureConfig_Private>& callback);

  
  
  
  
  
  
  
  
  int32_t GetCameraCapabilities(
      const CompletionCallbackWithOutput<CameraCapabilities_Private>& callback);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t CaptureStillImage(
      PPB_ImageCapture_Private_ShutterCallback shutter_callback,
      PPB_ImageCapture_Private_PreviewCallback preview_callback,
      PPB_ImageCapture_Private_JpegCallback jpeg_callback,
      int64_t* sequence_id);

  
  
  
  
  
  
  static bool IsImageCapture(const Resource& resource);
};

} 

#endif  

