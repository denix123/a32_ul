// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_CONTENT_VIDEO_CAPTURE_DEVICE_CORE_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_CONTENT_VIDEO_CAPTURE_DEVICE_CORE_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "base/threading/thread_checker.h"
#include "content/browser/media/capture/video_capture_oracle.h"
#include "content/common/content_export.h"
#include "media/base/video_frame.h"
#include "media/video/capture/video_capture_device.h"

namespace media {
class VideoCaptureParams;
class VideoFrame;
}  

namespace content {

const int kMinFrameWidth = 2;
const int kMinFrameHeight = 2;

template<typename IntType>
IntType MakeEven(IntType x) {
  return x & static_cast<IntType>(-2);
}

#if (defined(OS_WIN) || defined(OS_MACOSX)) || defined(USE_AURA)
const bool kAcceleratedSubscriberIsSupported = true;
#else
const bool kAcceleratedSubscriberIsSupported = false;
#endif

class VideoCaptureMachine;

class ThreadSafeCaptureOracle
    : public base::RefCountedThreadSafe<ThreadSafeCaptureOracle> {
 public:
  ThreadSafeCaptureOracle(scoped_ptr<media::VideoCaptureDevice::Client> client,
                          scoped_ptr<VideoCaptureOracle> oracle,
                          const media::VideoCaptureParams& params);

  
  
  
  
  typedef base::Callback<void(const scoped_refptr<media::VideoFrame>& frame,
                              base::TimeTicks timestamp,
                              bool success)> CaptureFrameCallback;

  bool ObserveEventAndDecideCapture(VideoCaptureOracle::Event event,
                                    const gfx::Rect& damage_rect,
                                    base::TimeTicks event_time,
                                    scoped_refptr<media::VideoFrame>* storage,
                                    CaptureFrameCallback* callback);

  base::TimeDelta min_capture_period() const {
    return oracle_->min_capture_period();
  }

  
  gfx::Size GetCaptureSize() const;

  
  
  void UpdateCaptureSize(const gfx::Size& source_size);

  
  void Stop();

  
  void ReportError(const std::string& reason);

 private:
  friend class base::RefCountedThreadSafe<ThreadSafeCaptureOracle>;
  virtual ~ThreadSafeCaptureOracle();

  
  void DidCaptureFrame(
      int frame_number,
      const scoped_refptr<media::VideoCaptureDevice::Client::Buffer>& buffer,
      const scoped_refptr<media::VideoFrame>& frame,
      base::TimeTicks timestamp,
      bool success);

  
  mutable base::Lock lock_;

  
  scoped_ptr<media::VideoCaptureDevice::Client> client_;

  
  const scoped_ptr<VideoCaptureOracle> oracle_;

  
  media::VideoCaptureParams params_;

  
  bool capture_size_updated_;

  
  media::VideoFrame::Format video_frame_format_;
};

class VideoCaptureMachine {
 public:
  VideoCaptureMachine() {}
  virtual ~VideoCaptureMachine() {}

  
  
  virtual bool Start(const scoped_refptr<ThreadSafeCaptureOracle>& oracle_proxy,
                     const media::VideoCaptureParams& params) = 0;

  
  
  virtual void Stop(const base::Closure& callback) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(VideoCaptureMachine);
};

class CONTENT_EXPORT ContentVideoCaptureDeviceCore
    : public base::SupportsWeakPtr<ContentVideoCaptureDeviceCore> {
 public:
  ContentVideoCaptureDeviceCore(
      scoped_ptr<VideoCaptureMachine> capture_machine);
  virtual ~ContentVideoCaptureDeviceCore();

  
  void AllocateAndStart(const media::VideoCaptureParams& params,
                        scoped_ptr<media::VideoCaptureDevice::Client> client);
  void StopAndDeAllocate();

 private:
  
  enum State {
    kIdle,
    kCapturing,
    kError
  };

  void TransitionStateTo(State next_state);

  
  
  void CaptureStarted(bool success);

  
  void Error(const std::string& reason);

  
  base::ThreadChecker thread_checker_;

  
  State state_;

  
  
  
  scoped_ptr<VideoCaptureMachine> capture_machine_;

  
  
  
  scoped_refptr<ThreadSafeCaptureOracle> oracle_proxy_;

  DISALLOW_COPY_AND_ASSIGN(ContentVideoCaptureDeviceCore);
};


}  

#endif  
