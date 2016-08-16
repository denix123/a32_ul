// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CLIENT_SOFTWARE_VIDEO_RENDERER_H_
#define REMOTING_CLIENT_SOFTWARE_VIDEO_RENDERER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "remoting/client/chromoting_stats.h"
#include "remoting/client/frame_consumer_proxy.h"
#include "remoting/client/frame_producer.h"
#include "remoting/client/video_renderer.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_geometry.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace remoting {

class ChromotingStats;

class SoftwareVideoRenderer : public VideoRenderer,
                              public FrameProducer,
                              public base::NonThreadSafe {
 public:
  
  
  
  
  
  SoftwareVideoRenderer(
      scoped_refptr<base::SingleThreadTaskRunner> main_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> decode_task_runner,
      scoped_refptr<FrameConsumerProxy> consumer);
  virtual ~SoftwareVideoRenderer();

  
  virtual void Initialize(const protocol::SessionConfig& config) OVERRIDE;
  virtual ChromotingStats* GetStats() OVERRIDE;
  virtual void ProcessVideoPacket(scoped_ptr<VideoPacket> packet,
                                  const base::Closure& done) OVERRIDE;

  
  
  
  
  
  
  
  virtual void DrawBuffer(webrtc::DesktopFrame* buffer) OVERRIDE;
  virtual void InvalidateRegion(const webrtc::DesktopRegion& region) OVERRIDE;
  virtual void RequestReturnBuffers(const base::Closure& done) OVERRIDE;
  virtual void SetOutputSizeAndClip(
      const webrtc::DesktopSize& view_size,
      const webrtc::DesktopRect& clip_area) OVERRIDE;

 private:
  class Core;

  
  
  void OnPacketDone(base::Time decode_start, const base::Closure& done);

  scoped_refptr<base::SingleThreadTaskRunner> decode_task_runner_;
  scoped_ptr<Core> core_;

  ChromotingStats stats_;

  
  int64 latest_sequence_number_;

  base::WeakPtrFactory<SoftwareVideoRenderer> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SoftwareVideoRenderer);
};

}  

#endif  
