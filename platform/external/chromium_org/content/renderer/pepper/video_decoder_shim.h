// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_VIDEO_DECODER_SHIM_H_
#define CONTENT_RENDERER_PEPPER_VIDEO_DECODER_SHIM_H_

#include <queue>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "media/base/video_decoder_config.h"
#include "media/video/video_decode_accelerator.h"

#include "ppapi/c/pp_codecs.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace gpu {
namespace gles2 {
class GLES2Interface;
}
}

namespace media {
class DecoderBuffer;
}

namespace webkit {
namespace gpu {
class ContextProviderWebContext;
}
}

namespace content {

class PepperVideoDecoderHost;

class VideoDecoderShim : public media::VideoDecodeAccelerator {
 public:
  explicit VideoDecoderShim(PepperVideoDecoderHost* host);
  virtual ~VideoDecoderShim();

  
  virtual bool Initialize(
      media::VideoCodecProfile profile,
      media::VideoDecodeAccelerator::Client* client) OVERRIDE;
  virtual void Decode(const media::BitstreamBuffer& bitstream_buffer) OVERRIDE;
  virtual void AssignPictureBuffers(
      const std::vector<media::PictureBuffer>& buffers) OVERRIDE;
  virtual void ReusePictureBuffer(int32 picture_buffer_id) OVERRIDE;
  virtual void Flush() OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual void Destroy() OVERRIDE;

 private:
  enum State {
    UNINITIALIZED,
    DECODING,
    FLUSHING,
    RESETTING,
  };

  struct PendingDecode;
  struct PendingFrame;
  class DecoderImpl;

  void OnInitializeComplete(int32_t result, uint32_t texture_pool_size);
  void OnDecodeComplete(int32_t result, uint32_t decode_id);
  void OnOutputComplete(scoped_ptr<PendingFrame> frame);
  void SendPictures();
  void OnResetComplete();
  void NotifyCompletedDecodes();
  void DismissTexture(uint32_t texture_id);
  void DeleteTexture(uint32_t texture_id);
  
  
  void FlushCommandBuffer();

  scoped_ptr<DecoderImpl> decoder_impl_;
  State state_;

  PepperVideoDecoderHost* host_;
  scoped_refptr<base::SingleThreadTaskRunner> media_task_runner_;
  scoped_refptr<webkit::gpu::ContextProviderWebContext> context_provider_;

  
  gfx::Size texture_size_;
  
  typedef base::hash_map<uint32_t, uint32_t> TextureIdMap;
  TextureIdMap texture_id_map_;
  
  typedef base::hash_set<uint32_t> TextureIdSet;
  TextureIdSet available_textures_;
  
  TextureIdSet textures_to_dismiss_;
  
  std::vector<gpu::Mailbox> pending_texture_mailboxes_;

  
  typedef std::queue<uint32_t> CompletedDecodeQueue;
  CompletedDecodeQueue completed_decodes_;

  
  
  typedef std::queue<linked_ptr<PendingFrame> > PendingFrameQueue;
  PendingFrameQueue pending_frames_;

  
  uint32_t texture_pool_size_;

  uint32_t num_pending_decodes_;

  base::WeakPtrFactory<VideoDecoderShim> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoDecoderShim);
};

}  

#endif  
