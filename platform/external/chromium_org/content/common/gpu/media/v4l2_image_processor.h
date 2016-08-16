// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_PROCESSOR_H_
#define CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_PROCESSOR_H_

#include <queue>
#include <vector>

#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "content/common/content_export.h"
#include "content/common/gpu/media/v4l2_video_device.h"
#include "media/base/video_frame.h"

namespace content {

class CONTENT_EXPORT V4L2ImageProcessor {
 public:
  explicit V4L2ImageProcessor(scoped_ptr<V4L2Device> device);
  virtual ~V4L2ImageProcessor();

  
  
  
  
  
  bool Initialize(media::VideoFrame::Format input_format,
                  media::VideoFrame::Format output_format,
                  gfx::Size input_visible_size,
                  gfx::Size output_visible_size,
                  gfx::Size output_allocated_size,
                  const base::Closure& error_cb);

  
  gfx::Size input_allocated_size() { return input_allocated_size_; }

  
  
  typedef base::Callback<void(const scoped_refptr<media::VideoFrame>& frame)>
      FrameReadyCB;

  
  
  
  void Process(const scoped_refptr<media::VideoFrame>& frame,
               const FrameReadyCB& cb);

  
  void Destroy();

 private:
  
  struct InputRecord {
    InputRecord();
    scoped_refptr<media::VideoFrame> frame;
    bool at_device;
  };

  
  struct OutputRecord {
    OutputRecord();
    bool at_device;
    bool at_client;
    std::vector<int> fds;
  };

  
  
  
  
  
  
  struct JobRecord {
    JobRecord();
    scoped_refptr<media::VideoFrame> frame;
    FrameReadyCB ready_cb;
  };

  enum {
    
    kInputBufferCount = 2,
    kOutputBufferCount = 2,
  };

  void ReuseOutputBuffer(int index);

  void Enqueue();
  void Dequeue();
  bool EnqueueInputRecord();
  bool EnqueueOutputRecord();
  bool CreateInputBuffers();
  bool CreateOutputBuffers();
  void DestroyInputBuffers();
  void DestroyOutputBuffers();

  void NotifyError();
  void DestroyTask();

  void ProcessTask(scoped_ptr<JobRecord> job_record);
  void ServiceDeviceTask();

  
  bool StartDevicePoll();
  bool StopDevicePoll();

  
  void DevicePollTask(bool poll_device);

  
  
  gfx::Size input_visible_size_;
  gfx::Size input_allocated_size_;

  
  gfx::Size output_visible_size_;
  gfx::Size output_allocated_size_;

  media::VideoFrame::Format input_format_;
  media::VideoFrame::Format output_format_;
  uint32 input_format_fourcc_;
  uint32 output_format_fourcc_;

  size_t input_planes_count_;
  size_t output_planes_count_;

  
  const scoped_refptr<base::MessageLoopProxy> child_message_loop_proxy_;

  
  scoped_ptr<V4L2Device> device_;

  
  base::Thread device_thread_;
  
  base::Thread device_poll_thread_;

  
  
  std::queue<linked_ptr<JobRecord> > input_queue_;
  std::queue<linked_ptr<JobRecord> > running_jobs_;

  
  bool input_streamon_;
  
  int input_buffer_queued_count_;
  
  std::vector<int> free_input_buffers_;
  
  std::vector<InputRecord> input_buffer_map_;

  
  bool output_streamon_;
  
  int output_buffer_queued_count_;
  
  std::vector<int> free_output_buffers_;
  
  std::vector<OutputRecord> output_buffer_map_;

  
  base::Closure error_cb_;

  
  base::WeakPtrFactory<V4L2ImageProcessor> device_weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(V4L2ImageProcessor);
};

}  

#endif  
