/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef PPAPI_CPP_PRIVATE_CAMERA_CAPABILITIES_PRIVATE_H_
#define PPAPI_CPP_PRIVATE_CAMERA_CAPABILITIES_PRIVATE_H_

#include "ppapi/c/private/ppb_camera_capabilities_private.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/size.h"

namespace pp {

class CameraCapabilities_Private : public Resource {
 public:
  
  
  CameraCapabilities_Private();

  
  
  
  
  CameraCapabilities_Private(const CameraCapabilities_Private& other);

  
  
  
  
  
  explicit CameraCapabilities_Private(const Resource& resource);

  
  
  
  
  explicit CameraCapabilities_Private(const InstanceHandle& instance);

  
  
  
  
  
  CameraCapabilities_Private(PassRef, PP_Resource resource);

  
  ~CameraCapabilities_Private();

  
  
  
  
  
  void GetSupportedPreviewSizes(std::vector<Size>* preview_sizes);

  
  
  
  
  
  void GetSupportedJpegSizes(std::vector<Size>* jpeg_sizes);

  
  
  
  
  
  
  
  
  static bool IsCameraCapabilities(const Resource& resource);
};

}  

#endif  

