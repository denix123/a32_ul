// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CODEC_VIDEO_ENCODER_VPX_H_
#define REMOTING_CODEC_VIDEO_ENCODER_VPX_H_

#include "base/callback.h"
#include "base/time/time.h"
#include "remoting/codec/scoped_vpx_codec.h"
#include "remoting/codec/video_encoder.h"
#include "remoting/codec/video_encoder_helper.h"

typedef struct vpx_image vpx_image_t;

namespace webrtc {
class DesktopRegion;
class DesktopSize;
}  

namespace remoting {

class VideoEncoderVpx : public VideoEncoder {
 public:
  
  static scoped_ptr<VideoEncoderVpx> CreateForVP8();
  static scoped_ptr<VideoEncoderVpx> CreateForVP9();

  virtual ~VideoEncoderVpx();

  
  virtual void SetLosslessEncode(bool want_lossless) OVERRIDE;
  virtual void SetLosslessColor(bool want_lossless) OVERRIDE;
  virtual scoped_ptr<VideoPacket> Encode(
      const webrtc::DesktopFrame& frame) OVERRIDE;

 private:
  explicit VideoEncoderVpx(bool use_vp9);

  
  bool Initialize(const webrtc::DesktopSize& size);

  
  
  void PrepareImage(const webrtc::DesktopFrame& frame,
                    webrtc::DesktopRegion* updated_region);

  
  
  void PrepareActiveMap(const webrtc::DesktopRegion& updated_region);

  
  bool use_vp9_;

  
  
  bool lossless_encode_;
  bool lossless_color_;

  ScopedVpxCodec codec_;
  base::TimeTicks timestamp_base_;

  
  scoped_ptr<vpx_image_t> image_;
  scoped_ptr<uint8[]> image_buffer_;

  
  scoped_ptr<uint8[]> active_map_;
  int active_map_width_;
  int active_map_height_;

  
  VideoEncoderHelper helper_;

  DISALLOW_COPY_AND_ASSIGN(VideoEncoderVpx);
};

}  

#endif  
