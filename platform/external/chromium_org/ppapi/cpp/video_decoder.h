// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_VIDEO_DECODER_H_
#define PPAPI_CPP_VIDEO_DECODER_H_

#include "ppapi/c/pp_codecs.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/size.h"


struct PP_FileInfo;

namespace pp {

class InstanceHandle;

class VideoDecoder : public Resource {
 public:
  
  
  VideoDecoder();

  
  
  
  
  explicit VideoDecoder(const InstanceHandle& instance);

  
  
  VideoDecoder(const VideoDecoder& other);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t Initialize(const Graphics3D& graphics3d_context,
                     PP_VideoProfile profile,
                     PP_HardwareAcceleration acceleration,
                     const CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t Decode(uint32_t decode_id,
                 uint32_t size,
                 const void* buffer,
                 const CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t GetPicture(
      const CompletionCallbackWithOutput<PP_VideoPicture>& callback);

  
  
  
  
  
  
  void RecyclePicture(const PP_VideoPicture& picture);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t Flush(const CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  
  
  
  
    
int32_t Reset(const CompletionCallback& callback);
};

}  

#endif  
