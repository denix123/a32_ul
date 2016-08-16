// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_VT_VIDEO_DECODE_ACCELERATOR_H_
#define CONTENT_COMMON_GPU_MEDIA_VT_VIDEO_DECODE_ACCELERATOR_H_

#include <stdint.h>

#include <map>
#include <queue>

#include "base/mac/scoped_cftyperef.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/thread.h"
#include "content/common/gpu/media/vt.h"
#include "media/filters/h264_parser.h"
#include "media/video/video_decode_accelerator.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gl/gl_context_cgl.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace content {

class VTVideoDecodeAccelerator
    : public media::VideoDecodeAccelerator,
      public base::NonThreadSafe {
 public:
  explicit VTVideoDecodeAccelerator(CGLContextObj cgl_context);
  virtual ~VTVideoDecodeAccelerator();

  
  virtual bool Initialize(
      media::VideoCodecProfile profile,
      Client* client) OVERRIDE;
  virtual void Decode(const media::BitstreamBuffer& bitstream) OVERRIDE;
  virtual void AssignPictureBuffers(
      const std::vector<media::PictureBuffer>& pictures) OVERRIDE;
  virtual void ReusePictureBuffer(int32_t picture_id) OVERRIDE;
  virtual void Flush() OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual bool CanDecodeOnIOThread() OVERRIDE;

  
  void Output(
      int32_t bitstream_id,
      OSStatus status,
      CVImageBufferRef image_buffer);

 private:
  struct DecodedFrame {
    DecodedFrame(int32_t bitstream_id, CVImageBufferRef image_buffer);
    ~DecodedFrame();

    int32_t bitstream_id;
    base::ScopedCFTypeRef<CVImageBufferRef> image_buffer;
  };

  
  
  enum Action {
    ACTION_FLUSH,
    ACTION_RESET,
    ACTION_DESTROY
  };

  
  
  struct PendingAction {
    PendingAction(Action action, int32_t bitstream_id);
    ~PendingAction();

    Action action;
    int32_t bitstream_id;
  };

  
  void ConfigureDecoder(
      const std::vector<const uint8_t*>& nalu_data_ptrs,
      const std::vector<size_t>& nalu_data_sizes);
  void DecodeTask(const media::BitstreamBuffer);
  void FlushTask();

  
  void OutputTask(DecodedFrame frame);
  void SizeChangedTask(gfx::Size coded_size);

  
  
  int32_t SendPictures(int32_t up_to_bitstream_id);

  
  
  
  
  
  void QueueAction(Action action);

  
  
  
  void ProcessDecodedFrames();

  
  
  void CompleteAction(Action action);

  
  
  void CompleteActions(int32_t bitstream_id);

  
  
  
  CGLContextObj cgl_context_;
  media::VideoDecodeAccelerator::Client* client_;
  gfx::Size texture_size_;
  std::queue<PendingAction> pending_actions_;
  std::queue<int32_t> pending_bitstream_ids_;

  
  
  std::map<int32_t, uint32_t> texture_ids_;

  
  std::queue<int32_t> available_picture_ids_;

  
  std::queue<DecodedFrame> decoded_frames_;

  
  std::map<int32_t, base::ScopedCFTypeRef<CVImageBufferRef>> picture_bindings_;

  
  
  
  VTDecompressionOutputCallbackRecord callback_;
  base::ScopedCFTypeRef<CMFormatDescriptionRef> format_;
  base::ScopedCFTypeRef<VTDecompressionSessionRef> session_;
  media::H264Parser parser_;
  gfx::Size coded_size_;

  
  
  
  scoped_refptr<base::SingleThreadTaskRunner> gpu_task_runner_;

  
  
  base::WeakPtrFactory<VTVideoDecodeAccelerator> weak_this_factory_;

  
  
  base::Thread decoder_thread_;

  DISALLOW_COPY_AND_ASSIGN(VTVideoDecodeAccelerator);
};

}  

#endif  
