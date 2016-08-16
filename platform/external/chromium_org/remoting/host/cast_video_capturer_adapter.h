// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_CAST_VIDEO_CAPTURER_ADAPTER_H_
#define REMOTING_HOST_CAST_VIDEO_CAPTURER_ADAPTER_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/timer/timer.h"
#include "third_party/libjingle/source/talk/media/base/videocapturer.h"
#include "third_party/webrtc/modules/desktop_capture/screen_capturer.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace webrtc {
class DesktopFrame;
}  

namespace remoting {

class CastVideoCapturerAdapter : public cricket::VideoCapturer,
                                 public webrtc::DesktopCapturer::Callback {
 public:
  explicit CastVideoCapturerAdapter(
      scoped_ptr<webrtc::DesktopCapturer> capturer);

  virtual ~CastVideoCapturerAdapter();

  
  virtual webrtc::SharedMemory* CreateSharedMemory(size_t size) OVERRIDE;
  
  
  virtual void OnCaptureCompleted(webrtc::DesktopFrame* frame) OVERRIDE;

  
  virtual bool GetBestCaptureFormat(const cricket::VideoFormat& desired,
                                  cricket::VideoFormat* best_format) OVERRIDE;
  virtual cricket::CaptureState Start(
      const cricket::VideoFormat& capture_format) OVERRIDE;
  virtual bool Pause(bool pause) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual bool IsRunning() OVERRIDE;
  virtual bool IsScreencast() const OVERRIDE;
  virtual bool GetPreferredFourccs(std::vector<uint32>* fourccs) OVERRIDE;

 private:
  
  
  void CaptureNextFrame();

  
  base::ThreadChecker thread_checker_;

  
  scoped_ptr<webrtc::DesktopCapturer> desktop_capturer_;

  
  scoped_ptr<base::RepeatingTimer<CastVideoCapturerAdapter> > capture_timer_;

  
  base::TimeTicks start_time_;

  DISALLOW_COPY_AND_ASSIGN(CastVideoCapturerAdapter);
};

}  

#endif  

