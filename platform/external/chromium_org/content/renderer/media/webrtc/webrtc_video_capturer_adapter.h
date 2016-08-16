// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_WEBRTC_VIDEO_CAPTURER_ADAPTER_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_WEBRTC_VIDEO_CAPTURER_ADAPTER_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "media/base/video_frame.h"
#include "media/video/capture/video_capture_types.h"
#include "third_party/libjingle/source/talk/media/base/videocapturer.h"

namespace content {

class CONTENT_EXPORT WebRtcVideoCapturerAdapter
    : NON_EXPORTED_BASE(public cricket::VideoCapturer) {
 public:
  explicit WebRtcVideoCapturerAdapter(bool is_screencast);
  virtual ~WebRtcVideoCapturerAdapter();

  
  
  
  virtual void OnFrameCaptured(const scoped_refptr<media::VideoFrame>& frame);

 private:
  
  
  virtual cricket::CaptureState Start(
      const cricket::VideoFormat& capture_format) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual bool IsRunning() OVERRIDE;
  virtual bool GetPreferredFourccs(std::vector<uint32>* fourccs) OVERRIDE;
  virtual bool GetBestCaptureFormat(const cricket::VideoFormat& desired,
                                    cricket::VideoFormat* best_format) OVERRIDE;
  virtual bool IsScreencast() const OVERRIDE;

  void UpdateI420Buffer(const scoped_refptr<media::VideoFrame>& src);

  
  base::ThreadChecker thread_checker_;

  const bool is_screencast_;
  bool running_;
  base::TimeDelta first_frame_timestamp_;
  
  
  
  uint8* buffer_;
  size_t buffer_size_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcVideoCapturerAdapter);
};

}  

#endif  
