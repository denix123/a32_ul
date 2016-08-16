// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_RTC_VIDEO_RENDERER_H_
#define CONTENT_RENDERER_MEDIA_RTC_VIDEO_RENDERER_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "content/common/content_export.h"
#include "content/common/media/video_capture.h"
#include "content/public/renderer/media_stream_video_sink.h"
#include "content/renderer/media/video_frame_provider.h"
#include "third_party/WebKit/public/platform/WebMediaStreamTrack.h"
#include "ui/gfx/size.h"

namespace base {
class MessageLoopProxy;
}

namespace content {

class CONTENT_EXPORT RTCVideoRenderer
    : NON_EXPORTED_BASE(public VideoFrameProvider),
      NON_EXPORTED_BASE(public MediaStreamVideoSink) {
 public:
  RTCVideoRenderer(const blink::WebMediaStreamTrack& video_track,
                   const base::Closure& error_cb,
                   const RepaintCB& repaint_cb);

  
  virtual void Start() OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual void Play() OVERRIDE;
  virtual void Pause() OVERRIDE;

 protected:
  virtual ~RTCVideoRenderer();

 private:
  enum State {
    STARTED,
    PAUSED,
    STOPPED,
  };

  void OnVideoFrame(const scoped_refptr<media::VideoFrame>& frame,
                    const media::VideoCaptureFormat& format,
                    const base::TimeTicks& estimated_capture_time);

  
  virtual void OnReadyStateChanged(
      blink::WebMediaStreamSource::ReadyState state) OVERRIDE;

  void RenderSignalingFrame();

  base::Closure error_cb_;
  RepaintCB repaint_cb_;
  scoped_refptr<base::MessageLoopProxy> message_loop_proxy_;
  State state_;
  gfx::Size frame_size_;
  blink::WebMediaStreamTrack video_track_;
  base::WeakPtrFactory<RTCVideoRenderer> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RTCVideoRenderer);
};

}  

#endif  
