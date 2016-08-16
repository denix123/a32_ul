// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_VIDEO_DESTINATION_HANDLER_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_VIDEO_DESTINATION_HANDLER_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "content/common/content_export.h"
#include "content/renderer/media/media_stream_video_source.h"
#include "media/base/video_frame_pool.h"

namespace content {

class PeerConnectionDependencyFactory;
class MediaStreamRegistryInterface;
class PPB_ImageData_Impl;

class CONTENT_EXPORT FrameWriterInterface {
 public:
  
  
  virtual void PutFrame(PPB_ImageData_Impl* image_data,
                        int64 time_stamp_ns) = 0;
  virtual ~FrameWriterInterface() {}
};

class CONTENT_EXPORT PpFrameWriter
    : NON_EXPORTED_BASE(public MediaStreamVideoSource),
      public FrameWriterInterface,
      NON_EXPORTED_BASE(public base::SupportsWeakPtr<PpFrameWriter>) {
 public:
  PpFrameWriter();
  virtual ~PpFrameWriter();

  
  
  virtual void PutFrame(PPB_ImageData_Impl* image_data,
                        int64 time_stamp_ns) OVERRIDE;
 protected:
  
  virtual void GetCurrentSupportedFormats(
      int max_requested_width,
      int max_requested_height,
      double max_requested_frame_rate,
      const VideoCaptureDeviceFormatsCB& callback) OVERRIDE;
  virtual void StartSourceImpl(
      const media::VideoCaptureFormat& format,
      const VideoCaptureDeliverFrameCB& frame_callback) OVERRIDE;
  virtual void StopSourceImpl() OVERRIDE;

 private:
  media::VideoFramePool frame_pool_;

  class FrameWriterDelegate;
  scoped_refptr<FrameWriterDelegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(PpFrameWriter);
};

class CONTENT_EXPORT VideoDestinationHandler {
 public:
  
  
  
  
  
  
  
  static bool Open(MediaStreamRegistryInterface* registry,
                   const std::string& url,
                   FrameWriterInterface** frame_writer);

 private:
  DISALLOW_COPY_AND_ASSIGN(VideoDestinationHandler);
};

}  

#endif  
