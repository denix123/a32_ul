// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_DECODE_ACCELERATOR_H_
#define CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_DECODE_ACCELERATOR_H_

#include <queue>
#include <vector>

#include "base/callback_forward.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "content/common/content_export.h"
#include "content/common/gpu/media/v4l2_video_device.h"
#include "media/base/limits.h"
#include "media/base/video_decoder_config.h"
#include "media/video/picture.h"
#include "media/video/video_decode_accelerator.h"
#include "ui/gfx/size.h"
#include "ui/gl/gl_bindings.h"

namespace base {
class MessageLoopProxy;
}  

namespace media {
class H264Parser;
}  

namespace content {
class CONTENT_EXPORT V4L2VideoDecodeAccelerator
    : public media::VideoDecodeAccelerator {
 public:
  V4L2VideoDecodeAccelerator(
      EGLDisplay egl_display,
      EGLContext egl_context,
      const base::WeakPtr<Client>& io_client_,
      const base::Callback<bool(void)>& make_context_current,
      scoped_ptr<V4L2Device> device,
      const scoped_refptr<base::MessageLoopProxy>& io_message_loop_proxy);
  virtual ~V4L2VideoDecodeAccelerator();

  
  
  virtual bool Initialize(media::VideoCodecProfile profile,
                          Client* client) OVERRIDE;
  virtual void Decode(const media::BitstreamBuffer& bitstream_buffer) OVERRIDE;
  virtual void AssignPictureBuffers(
      const std::vector<media::PictureBuffer>& buffers) OVERRIDE;
  virtual void ReusePictureBuffer(int32 picture_buffer_id) OVERRIDE;
  virtual void Flush() OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual bool CanDecodeOnIOThread() OVERRIDE;

 private:
  
  enum {
    kInputBufferCount = 8,
    
    
    
    kInputBufferMaxSizeFor1080p = 1024 * 1024,
    
    kInputBufferMaxSizeFor4k = 4 * kInputBufferMaxSizeFor1080p,
    
    
    
    
    kDpbOutputBufferExtraCount = media::limits::kMaxVideoFrames + 1,
  };

  
  enum State {
    kUninitialized,      
    kInitialized,        
    kDecoding,           
    kResetting,          
    kAfterReset,         
    kChangingResolution, 
                         
    kError,              
  };

  enum BufferId {
    kFlushBufferId = -2  
  };

  
  
  struct BitstreamBufferRef;

  
  struct EGLSyncKHRRef;

  
  struct PictureRecord;

  
  struct InputRecord {
    InputRecord();
    ~InputRecord();
    bool at_device;         
    void* address;          
    size_t length;          
    off_t bytes_used;       
    int32 input_id;         
  };

  
  struct OutputRecord {
    OutputRecord();
    ~OutputRecord();
    bool at_device;         
    bool at_client;         
    EGLImageKHR egl_image;  
    EGLSyncKHR egl_sync;    
    int32 picture_id;       
    bool cleared;           
                            
  };

  
  
  

  
  
  
  void DecodeTask(const media::BitstreamBuffer& bitstream_buffer);

  
  
  void DecodeBufferTask();
  
  bool AdvanceFrameFragment(const uint8* data, size_t size, size_t* endpos);
  
  void ScheduleDecodeBufferTaskIfNeeded();

  
  
  bool DecodeBufferInitial(const void* data, size_t size, size_t* endpos);
  bool DecodeBufferContinue(const void* data, size_t size);

  
  
  
  bool AppendToInputFrame(const void* data, size_t size);
  
  bool FlushInputFrame();

  
  
  
  void ServiceDeviceTask(bool event_pending);
  
  void Enqueue();
  void Dequeue();
  
  void DequeueEvents();
  
  bool EnqueueInputRecord();
  bool EnqueueOutputRecord();

  
  
  
  void ReusePictureBufferTask(int32 picture_buffer_id,
                              scoped_ptr<EGLSyncKHRRef> egl_sync_ref);

  
  
  
  void FlushTask();
  
  
  
  void NotifyFlushDoneIfNeeded();

  
  
  
  void ResetTask();
  
  
  void ResetDoneTask();

  
  void DestroyTask();

  
  bool StartDevicePoll();
  
  
  bool StopDevicePoll(bool keep_input_state);

  void StartResolutionChangeIfNeeded();
  void FinishResolutionChange();

  
  
  bool GetFormatInfo(struct v4l2_format* format, bool* again);
  
  bool CreateBuffersForFormat(const struct v4l2_format& format);

  
  
  

  
  void DevicePollTask(bool poll_device);

  
  
  

  
  void NotifyError(Error error);

  
  
  void SetDecoderState(State state);

  
  
  
  
  

  
  bool CreateInputBuffers();
  bool CreateOutputBuffers();

  
  
  

  
  void DestroyInputBuffers();
  
  
  
  
  
  bool DestroyOutputBuffers();
  void ResolutionChangeDestroyBuffers();

  
  void SendPictureReady();

  
  void PictureCleared();

  
  
  
  
  bool IsResolutionChangeNecessary();

  
  scoped_refptr<base::MessageLoopProxy> child_message_loop_proxy_;

  
  scoped_refptr<base::MessageLoopProxy> io_message_loop_proxy_;

  
  
  
  
  
  
  base::WeakPtr<V4L2VideoDecodeAccelerator> weak_this_;

  
  
  
  scoped_ptr<base::WeakPtrFactory<Client> > client_ptr_factory_;
  base::WeakPtr<Client> client_;
  
  base::WeakPtr<Client> io_client_;

  
  
  
  
  
  

  
  
  base::Thread decoder_thread_;
  
  State decoder_state_;
  
  scoped_ptr<BitstreamBufferRef> decoder_current_bitstream_buffer_;
  
  scoped_ptr<V4L2Device> device_;
  
  
  
  int decoder_delay_bitstream_buffer_id_;
  
  int decoder_current_input_buffer_;
  
  
  
  int decoder_decode_buffer_tasks_scheduled_;
  
  int decoder_frames_at_client_;
  
  bool decoder_flushing_;
  
  
  bool resolution_change_pending_;
  
  bool resolution_change_reset_pending_;
  
  std::queue<linked_ptr<BitstreamBufferRef> > decoder_input_queue_;
  
  
  scoped_ptr<media::H264Parser> decoder_h264_parser_;
  
  bool decoder_partial_frame_pending_;

  
  
  
  
  
  
  
  

  
  std::queue<int> input_ready_queue_;

  
  bool input_streamon_;
  
  int input_buffer_queued_count_;
  
  std::vector<int> free_input_buffers_;
  
  std::vector<InputRecord> input_buffer_map_;

  
  bool output_streamon_;
  
  int output_buffer_queued_count_;
  
  
  std::queue<int> free_output_buffers_;
  
  std::vector<OutputRecord> output_buffer_map_;
  
  int output_dpb_size_;
  
  size_t output_planes_count_;

  
  std::queue<PictureRecord> pending_picture_ready_;

  
  int picture_clearing_count_;

  
  
  base::WaitableEvent pictures_assigned_;

  
  gfx::Size frame_buffer_size_;

  
  
  

  
  base::Thread device_poll_thread_;

  
  
  

  
  base::Callback<bool(void)> make_context_current_;

  
  EGLDisplay egl_display_;
  EGLContext egl_context_;

  
  media::VideoCodecProfile video_profile_;

  
  base::WeakPtrFactory<V4L2VideoDecodeAccelerator> weak_this_factory_;

  DISALLOW_COPY_AND_ASSIGN(V4L2VideoDecodeAccelerator);
};

}  

#endif  
