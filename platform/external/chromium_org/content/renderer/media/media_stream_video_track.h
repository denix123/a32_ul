// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_VIDEO_TRACK_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_VIDEO_TRACK_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "content/public/renderer/media_stream_video_sink.h"
#include "content/renderer/media/media_stream_track.h"
#include "content/renderer/media/media_stream_video_source.h"

namespace content {

class CONTENT_EXPORT MediaStreamVideoTrack : public MediaStreamTrack {
 public:
  
  
  
  
  
  
  
  
  static blink::WebMediaStreamTrack CreateVideoTrack(
      MediaStreamVideoSource* source,
      const blink::WebMediaConstraints& constraints,
      const MediaStreamVideoSource::ConstraintsCallback& callback,
      bool enabled);

  static MediaStreamVideoTrack* GetVideoTrack(
      const blink::WebMediaStreamTrack& track);

  
  MediaStreamVideoTrack(
      MediaStreamVideoSource* source,
      const blink::WebMediaConstraints& constraints,
      const MediaStreamVideoSource::ConstraintsCallback& callback,
      bool enabled);
  virtual ~MediaStreamVideoTrack();

  virtual void SetEnabled(bool enabled) OVERRIDE;

  virtual void Stop() OVERRIDE;

  void OnReadyStateChanged(blink::WebMediaStreamSource::ReadyState state);

  const blink::WebMediaConstraints& constraints() const {
    return constraints_;
  }

 protected:
  
  base::ThreadChecker thread_checker_;

 private:
  
  
  friend class MediaStreamVideoSink;
  FRIEND_TEST_ALL_PREFIXES(MediaStreamRemoteVideoSourceTest, StartTrack);
  FRIEND_TEST_ALL_PREFIXES(MediaStreamRemoteVideoSourceTest, RemoteTrackStop);
  FRIEND_TEST_ALL_PREFIXES(VideoDestinationHandlerTest, PutFrame);

  
  
  
  
  
  
  void AddSink(MediaStreamVideoSink* sink,
               const VideoCaptureDeliverFrameCB& callback);
  void RemoveSink(MediaStreamVideoSink* sink);

  std::vector<MediaStreamVideoSink*> sinks_;

  
  
  class FrameDeliverer;
  scoped_refptr<FrameDeliverer> frame_deliverer_;

  blink::WebMediaConstraints constraints_;

  
  
  
  MediaStreamVideoSource* source_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamVideoTrack);
};

}  

#endif  
