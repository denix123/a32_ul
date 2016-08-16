// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_ENCODE_ACCELERATOR_H_
#define CONTENT_COMMON_GPU_MEDIA_V4L2_VIDEO_ENCODE_ACCELERATOR_H_

#include <list>
#include <linux/videodev2.h>
#include <vector>

#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "content/common/content_export.h"
#include "content/common/gpu/media/v4l2_image_processor.h"
#include "content/common/gpu/media/v4l2_video_device.h"
#include "media/video/video_encode_accelerator.h"
#include "ui/gfx/size.h"

namespace base {

class MessageLoopProxy;

}  

namespace media {

class BitstreamBuffer;

}  

namespace content {

class CONTENT_EXPORT V4L2VideoEncodeAccelerator
    : public media::VideoEncodeAccelerator {
 public:
  explicit V4L2VideoEncodeAccelerator(scoped_ptr<V4L2Device> device);
  virtual ~V4L2VideoEncodeAccelerator();

  static std::vector<media::VideoEncodeAccelerator::SupportedProfile>
      GetSupportedProfilesStatic();

  
  virtual std::vector<media::VideoEncodeAccelerator::SupportedProfile>
      GetSupportedProfiles() OVERRIDE;
  virtual bool Initialize(media::VideoFrame::Format format,
                          const gfx::Size& input_visible_size,
                          media::VideoCodecProfile output_profile,
                          uint32 initial_bitrate,
                          Client* client) OVERRIDE;
  virtual void Encode(const scoped_refptr<media::VideoFrame>& frame,
                      bool force_keyframe) OVERRIDE;
  virtual void UseOutputBitstreamBuffer(const media::BitstreamBuffer& buffer)
      OVERRIDE;
  virtual void RequestEncodingParametersChange(uint32 bitrate,
                                               uint32 framerate) OVERRIDE;
  virtual void Destroy() OVERRIDE;

 private:
  
  
  struct BitstreamBufferRef;

  
  struct InputRecord {
    InputRecord();
    bool at_device;
    scoped_refptr<media::VideoFrame> frame;
  };

  
  struct OutputRecord {
    OutputRecord();
    bool at_device;
    linked_ptr<BitstreamBufferRef> buffer_ref;
    void* address;
    size_t length;
  };

  enum {
    kInitialFramerate = 30,
    
    kInputBufferCount = 2,
    kOutputBufferCount = 2,
    kOutputBufferSize = (2 * 1024 * 1024),
  };

  
  enum State {
    kUninitialized,  
    kInitialized,    
    kEncoding,       
    kError,          
  };

  
  
  

  
  void FrameProcessed(bool force_keyframe,
                      const scoped_refptr<media::VideoFrame>& frame);

  
  void ImageProcessorError();

  
  
  

  void EncodeTask(const scoped_refptr<media::VideoFrame>& frame,
                  bool force_keyframe);

  
  
  void UseOutputBitstreamBufferTask(scoped_ptr<BitstreamBufferRef> buffer_ref);

  
  void DestroyTask();

  
  
  void ServiceDeviceTask();

  
  void Enqueue();
  void Dequeue();
  
  bool EnqueueInputRecord();
  bool EnqueueOutputRecord();

  
  bool StartDevicePoll();
  bool StopDevicePoll();

  
  
  

  
  void DevicePollTask(bool poll_device);

  
  
  

  
  void NotifyError(Error error);

  
  
  void SetEncoderState(State state);

  
  
  
  
  

  
  void RequestEncodingParametersChangeTask(uint32 bitrate, uint32 framerate);

  
  bool SetFormats(media::VideoFrame::Format input_format,
                  media::VideoCodecProfile output_profile);

  
  
  
  bool NegotiateInputFormat(media::VideoFrame::Format input_format);

  
  bool SetOutputFormat(media::VideoCodecProfile output_profile);

  
  bool InitControls();

  
  bool CreateInputBuffers();
  bool CreateOutputBuffers();

  
  void DestroyInputBuffers();
  void DestroyOutputBuffers();

  
  const scoped_refptr<base::MessageLoopProxy> child_message_loop_proxy_;

  gfx::Size visible_size_;
  
  gfx::Size input_allocated_size_;
  size_t output_buffer_byte_size_;

  
  media::VideoFrame::Format device_input_format_;
  size_t input_planes_count_;
  uint32 output_format_fourcc_;

  
  
  
  
  
  

  
  State encoder_state_;

  
  
  scoped_ptr<uint8[]> stream_header_;
  size_t stream_header_size_;

  
  std::list<scoped_refptr<media::VideoFrame> > encoder_input_queue_;

  
  scoped_ptr<V4L2Device> device_;

  
  bool input_streamon_;
  
  int input_buffer_queued_count_;
  
  std::vector<int> free_input_buffers_;
  
  std::vector<InputRecord> input_buffer_map_;
  enum v4l2_memory input_memory_type_;

  
  bool output_streamon_;
  
  int output_buffer_queued_count_;
  
  std::vector<int> free_output_buffers_;
  
  std::vector<OutputRecord> output_buffer_map_;

  
  
  std::vector<linked_ptr<BitstreamBufferRef> > encoder_output_queue_;

  
  scoped_ptr<V4L2ImageProcessor> image_processor_;

  
  
  base::Thread encoder_thread_;

  
  
  base::Thread device_poll_thread_;

  
  
  
  base::WeakPtr<Client> client_;
  scoped_ptr<base::WeakPtrFactory<Client> > client_ptr_factory_;

  
  
  
  
  base::WeakPtr<V4L2VideoEncodeAccelerator> weak_this_;
  base::WeakPtrFactory<V4L2VideoEncodeAccelerator> weak_this_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(V4L2VideoEncodeAccelerator);
};

}  

#endif  
