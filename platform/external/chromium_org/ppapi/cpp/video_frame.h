// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_VIDEO_FRAME_H_
#define PPAPI_CPP_VIDEO_FRAME_H_

#include "ppapi/c/ppb_video_frame.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/size.h"

namespace pp {

class VideoFrame : public Resource {
 public:
  
  
  VideoFrame();

  
  
  
  VideoFrame(const VideoFrame& other);

  
  
  
  explicit VideoFrame(const Resource& resource);

  
  
  
  
  VideoFrame(PassRef, PP_Resource resource);

  virtual ~VideoFrame();

  
  
  
  
  PP_TimeDelta GetTimestamp() const;

  
  
  
  
  
  void SetTimestamp(PP_TimeDelta timestamp);

  
  
  
  
  PP_VideoFrame_Format GetFormat() const;

  
  
  
  
  
  bool GetSize(Size* size) const;

  
  
  
  void* GetDataBuffer();

  
  
  
  uint32_t GetDataBufferSize() const;
};

}  

#endif  
