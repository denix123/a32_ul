/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef PPAPI_CPP_PRIVATE_IMAGE_CAPTURE_CONFIG_PRIVATE_H_
#define PPAPI_CPP_PRIVATE_IMAGE_CAPTURE_CONFIG_PRIVATE_H_

#include "ppapi/c/private/ppb_image_capture_config_private.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/size.h"

namespace pp {

class ImageCaptureConfig_Private {
 public:
  
  
  ImageCaptureConfig_Private();

  
  
  
  
  ImageCaptureConfig_Private(const ImageCaptureConfig_Private& other);

  
  
  
  
  
  explicit ImageCaptureConfig_Private(const Resource& resource);

  
  
  
  
  explicit ImageCaptureConfig_Private(const InstanceHandle& instance);

  
  
  
  
  
  ImageCaptureConfig_Private(PassRef, PP_Resource resource);

  
  ~ImageCaptureConfig_Private();

  
  
  
  
  
  void GetPreviewSize(Size* preview_size);

  
  
  
  
  
  void SetPreviewSize(const Size& preview_size);

  
  
  
  
  
  void GetJpegSize(Size* jpeg_size);

  
  
  
  
  
  void SetJpegSize(const Size& jpeg_size);

  
  
  
  
  
  
  
  
  static bool IsImageCaptureConfig(const Resource& resource);
};

} 

#endif  

