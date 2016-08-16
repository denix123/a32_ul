// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CLIENT_PLUGIN_MEDIA_SOURCE_VIDEO_RENDERER_H_
#define REMOTING_CLIENT_PLUGIN_MEDIA_SOURCE_VIDEO_RENDERER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "remoting/client/chromoting_stats.h"
#include "remoting/client/video_renderer.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_geometry.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_region.h"

namespace remoting {

class MediaSourceVideoRenderer : public VideoRenderer {
 public:
  class Delegate {
   public:
    Delegate() {}
    virtual ~Delegate() {}

    
    virtual void OnMediaSourceSize(const webrtc::DesktopSize& size,
                                   const webrtc::DesktopVector& dpi) = 0;

    
    virtual void OnMediaSourceShape(const webrtc::DesktopRegion& shape) = 0;

    
    
    virtual void OnMediaSourceReset(const std::string& format) = 0;

    
    virtual void OnMediaSourceData(uint8_t* buffer, size_t buffer_size,
                                   bool keyframe) = 0;
  };

  explicit MediaSourceVideoRenderer(Delegate* delegate);
  virtual ~MediaSourceVideoRenderer();

  
  virtual void Initialize(const protocol::SessionConfig& config) OVERRIDE;
  virtual ChromotingStats* GetStats() OVERRIDE;
  virtual void ProcessVideoPacket(scoped_ptr<VideoPacket> packet,
                                  const base::Closure& done) OVERRIDE;

 private:
  
  class VideoWriter;

  Delegate* delegate_;

  std::string format_string_;
  const char* codec_id_;

  scoped_ptr<VideoWriter> writer_;
  webrtc::DesktopVector frame_dpi_;
  webrtc::DesktopRegion desktop_shape_;

  ChromotingStats stats_;
  int64 latest_sequence_number_;

  DISALLOW_COPY_AND_ASSIGN(MediaSourceVideoRenderer);
};

}  

#endif  
