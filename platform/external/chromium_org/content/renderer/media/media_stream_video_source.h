// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_VIDEO_SOURCE_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_VIDEO_SOURCE_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/non_thread_safe.h"
#include "content/common/content_export.h"
#include "content/common/media/video_capture.h"
#include "content/public/renderer/media_stream_video_sink.h"
#include "content/renderer/media/media_stream_source.h"
#include "media/base/video_frame.h"
#include "media/video/capture/video_capture_types.h"
#include "third_party/WebKit/public/platform/WebMediaConstraints.h"
#include "third_party/WebKit/public/platform/WebMediaStreamSource.h"
#include "third_party/WebKit/public/platform/WebMediaStreamTrack.h"

namespace content {

class MediaStreamVideoTrack;
class VideoTrackAdapter;

class CONTENT_EXPORT MediaStreamVideoSource
    : public MediaStreamSource,
      NON_EXPORTED_BASE(public base::NonThreadSafe) {
 public:
  MediaStreamVideoSource();
  virtual ~MediaStreamVideoSource();

  
  static MediaStreamVideoSource* GetVideoSource(
      const blink::WebMediaStreamSource& source);

  
  void AddTrack(MediaStreamVideoTrack* track,
                const VideoCaptureDeliverFrameCB& frame_callback,
                const blink::WebMediaConstraints& constraints,
                const ConstraintsCallback& callback);
  void RemoveTrack(MediaStreamVideoTrack* track);

  
  static bool IsConstraintSupported(const std::string& name);

  
  const scoped_refptr<base::MessageLoopProxy>& io_message_loop() const;

  
  
  static const char kMinAspectRatio[];  
  static const char kMaxAspectRatio[];  
  static const char kMaxWidth[];  
  static const char kMinWidth[];  
  static const char kMaxHeight[];  
  static const char kMinHeight[];  
  static const char kMaxFrameRate[];  
  static const char kMinFrameRate[];  

  
  
  static const int kDefaultWidth;
  static const int kDefaultHeight;
  static const int kDefaultFrameRate;
  static const int kUnknownFrameRate;

 protected:
  virtual void DoStopSource() OVERRIDE;

  
  virtual void SetReadyState(blink::WebMediaStreamSource::ReadyState state);

  
  virtual void SetMutedState(bool state);

  
  
  
  
  
  
  virtual void GetCurrentSupportedFormats(
      int max_requested_width,
      int max_requested_height,
      double max_requested_frame_rate,
      const VideoCaptureDeviceFormatsCB& callback) = 0;

  
  
  
  
  virtual void StartSourceImpl(
      const media::VideoCaptureFormat& format,
      const VideoCaptureDeliverFrameCB& frame_callback) = 0;
  void OnStartDone(MediaStreamRequestResult result);

  
  
  
  virtual void StopSourceImpl() = 0;

  enum State {
    NEW,
    RETRIEVING_CAPABILITIES,
    STARTING,
    STARTED,
    ENDED
  };
  State state() const { return state_; }

 private:
  void OnSupportedFormats(const media::VideoCaptureFormats& formats);

  
  
  
  bool FindBestFormatWithConstraints(
      const media::VideoCaptureFormats& formats,
      media::VideoCaptureFormat* best_format);

  
  
  
  
  
  
  
  void FinalizeAddTrack();

  State state_;

  media::VideoCaptureFormat current_format_;

  struct RequestedConstraints {
    RequestedConstraints(MediaStreamVideoTrack* track,
                         const VideoCaptureDeliverFrameCB& frame_callback,
                         const blink::WebMediaConstraints& constraints,
                         const ConstraintsCallback& callback);
    ~RequestedConstraints();

    MediaStreamVideoTrack* track;
    VideoCaptureDeliverFrameCB frame_callback;
    blink::WebMediaConstraints constraints;
    ConstraintsCallback callback;
  };
  std::vector<RequestedConstraints> requested_constraints_;

  media::VideoCaptureFormats supported_formats_;

  
  scoped_refptr<VideoTrackAdapter> track_adapter_;

  
  std::vector<MediaStreamVideoTrack*> tracks_;

  
  base::WeakPtrFactory<MediaStreamVideoSource> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamVideoSource);
};

}  

#endif  
