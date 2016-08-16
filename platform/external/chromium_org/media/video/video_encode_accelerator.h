// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_VIDEO_VIDEO_ENCODE_ACCELERATOR_H_
#define MEDIA_VIDEO_VIDEO_ENCODE_ACCELERATOR_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "media/base/bitstream_buffer.h"
#include "media/base/media_export.h"
#include "media/base/video_decoder_config.h"
#include "media/base/video_frame.h"

namespace media {

class BitstreamBuffer;
class VideoFrame;

class MEDIA_EXPORT VideoEncodeAccelerator {
 public:
  
  struct SupportedProfile {
    VideoCodecProfile profile;
    gfx::Size max_resolution;
    uint32 max_framerate_numerator;
    uint32 max_framerate_denominator;
  };

  
  enum Error {
    
    kIllegalStateError,
    
    kInvalidArgumentError,
    
    
    
    
    kPlatformFailureError,
    kErrorMax = kPlatformFailureError
  };

  
  
  class MEDIA_EXPORT Client {
   public:
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void RequireBitstreamBuffers(unsigned int input_count,
                                         const gfx::Size& input_coded_size,
                                         size_t output_buffer_size) = 0;

    
    
    
    
    
    
    virtual void BitstreamBufferReady(int32 bitstream_buffer_id,
                                      size_t payload_size,
                                      bool key_frame) = 0;

    
    
    
    virtual void NotifyError(Error error) = 0;

   protected:
    
    
    virtual ~Client() {}
  };

  

  
  
  virtual std::vector<SupportedProfile> GetSupportedProfiles() = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual bool Initialize(VideoFrame::Format input_format,
                          const gfx::Size& input_visible_size,
                          VideoCodecProfile output_profile,
                          uint32 initial_bitrate,
                          Client* client) = 0;

  
  
  
  
  virtual void Encode(const scoped_refptr<VideoFrame>& frame,
                      bool force_keyframe) = 0;

  
  
  
  
  
  virtual void UseOutputBitstreamBuffer(const BitstreamBuffer& buffer) = 0;

  
  
  
  
  
  virtual void RequestEncodingParametersChange(uint32 bitrate,
                                               uint32 framerate) = 0;

  
  
  
  
  
  virtual void Destroy() = 0;

 protected:
  
  
  virtual ~VideoEncodeAccelerator();
};

}  

namespace base {

template <class T>
struct DefaultDeleter;

template <>
struct MEDIA_EXPORT DefaultDeleter<media::VideoEncodeAccelerator> {
 public:
  void operator()(void* video_encode_accelerator) const;
};

}  

#endif  
