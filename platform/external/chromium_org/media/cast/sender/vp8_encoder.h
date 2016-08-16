// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_SENDER_CODECS_VP8_VP8_ENCODER_H_
#define MEDIA_CAST_SENDER_CODECS_VP8_VP8_ENCODER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "media/cast/cast_config.h"
#include "media/cast/sender/software_video_encoder.h"
#include "third_party/libvpx/source/libvpx/vpx/vpx_encoder.h"

namespace media {
class VideoFrame;
}

typedef struct vpx_codec_ctx vpx_enc_ctx_t;

namespace media {
namespace cast {

const int kNumberOfVp8VideoBuffers = 3;

class Vp8Encoder : public SoftwareVideoEncoder {
 public:
  Vp8Encoder(const VideoSenderConfig& video_config, int max_unacked_frames);

  virtual ~Vp8Encoder();

  
  
  virtual void Initialize() OVERRIDE;

  
  virtual bool Encode(const scoped_refptr<media::VideoFrame>& video_frame,
                      EncodedFrame* encoded_image) OVERRIDE;

  
  virtual void UpdateRates(uint32 new_bitrate) OVERRIDE;

  
  virtual void GenerateKeyFrame() OVERRIDE;

  virtual void LatestFrameIdToReference(uint32 frame_id) OVERRIDE;

 private:
  enum Vp8Buffers {
    kAltRefBuffer = 0,
    kGoldenBuffer = 1,
    kLastBuffer = 2,
    kNoBuffer = 3  
  };

  enum Vp8BufferState {
    kBufferStartState,
    kBufferSent,
    kBufferAcked
  };
  struct BufferState {
    uint32 frame_id;
    Vp8BufferState state;
  };

  void InitEncode(int number_of_cores);

  
  uint32 MaxIntraTarget(uint32 optimal_buffer_size) const;

  
  Vp8Buffers GetNextBufferToUpdate();

  
  
  uint32 GetCodecReferenceFlags(vpx_codec_flags_t* flags);

  
  void GetCodecUpdateFlags(Vp8Buffers buffer_to_update,
                           vpx_codec_flags_t* flags);

  const VideoSenderConfig cast_config_;
  const bool use_multiple_video_buffers_;

  
  scoped_ptr<vpx_codec_enc_cfg_t> config_;
  scoped_ptr<vpx_enc_ctx_t> encoder_;
  vpx_image_t* raw_image_;

  bool key_frame_requested_;
  bool first_frame_received_;
  base::TimeDelta first_frame_timestamp_;
  uint32 last_encoded_frame_id_;
  uint32 last_acked_frame_id_;
  uint32 frame_id_to_reference_;
  uint32 undroppable_frames_;
  BufferState buffer_state_[kNumberOfVp8VideoBuffers];

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(Vp8Encoder);
};

}  
}  

#endif  
