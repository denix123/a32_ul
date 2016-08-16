// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_MEDIA_STREAM_VIDEO_SINK_H_
#define CONTENT_PUBLIC_RENDERER_MEDIA_STREAM_VIDEO_SINK_H_

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/public/renderer/media_stream_sink.h"

namespace media {
class VideoCaptureFormat;
class VideoFrame;
}

namespace blink {
class WebMediaStreamTrack;
}

namespace content {

typedef base::Callback<
  void(const scoped_refptr<media::VideoFrame>& video_frame,
       const media::VideoCaptureFormat& format,
       const base::TimeTicks& estimated_capture_time)>
    VideoCaptureDeliverFrameCB;

class CONTENT_EXPORT MediaStreamVideoSink : public MediaStreamSink {
 public:
  
  
  
  
  
  
  
  
  
  
  static void AddToVideoTrack(MediaStreamVideoSink* sink,
                              const VideoCaptureDeliverFrameCB& callback,
                              const blink::WebMediaStreamTrack& track);
  static void RemoveFromVideoTrack(MediaStreamVideoSink* sink,
                                   const blink::WebMediaStreamTrack& track);

 protected:
  virtual ~MediaStreamVideoSink() {}
};


}  

#endif  
