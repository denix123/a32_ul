// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_VIDEO_FRAME_RECORDER_H_
#define REMOTING_HOST_VIDEO_FRAME_RECORDER_H_

#include <stdint.h>
#include <list>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"

namespace webrtc {
class DesktopFrame;
}

namespace remoting {

class VideoEncoder;


class VideoFrameRecorder {
 public:
  VideoFrameRecorder();
  virtual ~VideoFrameRecorder();

  
  
  
  
  
  scoped_ptr<VideoEncoder> WrapVideoEncoder(scoped_ptr<VideoEncoder> encoder);

  
  
  
  void DetachVideoEncoderWrapper();

  
  void SetEnableRecording(bool enable_recording);

  
  
  
  void SetMaxContentBytes(int64_t max_content_bytes);

  
  scoped_ptr<webrtc::DesktopFrame> NextFrame();

 private:
  class RecordingVideoEncoder;
  friend class RecordingVideoEncoder;

  void SetEncoderTaskRunner(scoped_refptr<base::TaskRunner> task_runner);
  void RecordFrame(scoped_ptr<webrtc::DesktopFrame> frame);

  
  std::list<webrtc::DesktopFrame*> recorded_frames_;

  
  int64_t content_bytes_;

  
  int64_t max_content_bytes_;

  
  bool enable_recording_;

  
  scoped_refptr<base::TaskRunner> encoder_task_runner_;

  
  base::WeakPtr<RecordingVideoEncoder> recording_encoder_;

  scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner_;
  base::WeakPtrFactory<VideoFrameRecorder> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoFrameRecorder);
};

}  

#endif  
