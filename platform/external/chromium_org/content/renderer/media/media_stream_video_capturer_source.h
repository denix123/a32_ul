// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_VIDEO_CAPTURER_SOURCE_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_VIDEO_CAPTURER_SOURCE_H_

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/threading/thread_checker.h"
#include "content/common/media/video_capture.h"
#include "content/renderer/media/media_stream_video_source.h"

namespace content {

class CONTENT_EXPORT VideoCapturerDelegate
    : public base::RefCountedThreadSafe<VideoCapturerDelegate> {
 public:
  typedef base::Callback<void(MediaStreamRequestResult result)> RunningCallback;

  explicit VideoCapturerDelegate(const StreamDeviceInfo& device_info);

  
  
  
  
  
  virtual void GetCurrentSupportedFormats(
      int max_requested_width,
      int max_requested_height,
      double max_requested_frame_rate,
      const VideoCaptureDeviceFormatsCB& callback);

  
  
  
  
  
  
  virtual void StartCapture(
      const media::VideoCaptureParams& params,
      const VideoCaptureDeliverFrameCB& new_frame_callback,
      const RunningCallback& running_callback);

  
  
  virtual void StopCapture();

 private:
  FRIEND_TEST_ALL_PREFIXES(MediaStreamVideoCapturerSourceTest, Ended);
  friend class base::RefCountedThreadSafe<VideoCapturerDelegate>;
  friend class MockVideoCapturerDelegate;

  virtual ~VideoCapturerDelegate();

  void OnStateUpdateOnRenderThread(VideoCaptureState state);
  void OnDeviceFormatsInUseReceived(const media::VideoCaptureFormats& formats);
  void OnDeviceSupportedFormatsEnumerated(
      const media::VideoCaptureFormats& formats);

  
  
  media::VideoCaptureSessionId session_id_;
  base::Closure release_device_cb_;
  base::Closure stop_capture_cb_;

  bool is_screen_cast_;

  
  
  RunningCallback running_callback_;

  VideoCaptureDeviceFormatsCB source_formats_callback_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(VideoCapturerDelegate);
};

class CONTENT_EXPORT MediaStreamVideoCapturerSource
    : public MediaStreamVideoSource {
 public:
  MediaStreamVideoCapturerSource(
      const StreamDeviceInfo& device_info,
      const SourceStoppedCallback& stop_callback,
      const scoped_refptr<VideoCapturerDelegate>& delegate);

  virtual ~MediaStreamVideoCapturerSource();

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
  
  scoped_refptr<VideoCapturerDelegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamVideoCapturerSource);
};

}  

#endif  
