// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_VIDEO_VIDEO_DECODE_ACCELERATOR_H_
#define MEDIA_VIDEO_VIDEO_DECODE_ACCELERATOR_H_

#include <vector>

#include "base/basictypes.h"
#include "media/base/bitstream_buffer.h"
#include "media/base/video_decoder_config.h"
#include "media/video/picture.h"
#include "ui/gfx/size.h"

namespace media {

class MEDIA_EXPORT VideoDecodeAccelerator {
 public:
  
  
  
  
  enum Error {
    
    ILLEGAL_STATE = 1,
    
    INVALID_ARGUMENT,
    
    UNREADABLE_INPUT,
    
    
    
    PLATFORM_FAILURE,
    
    LARGEST_ERROR_ENUM,
  };

  
  
  
  
  
  
  class MEDIA_EXPORT Client {
   public:
    
    virtual void ProvidePictureBuffers(uint32 requested_num_of_buffers,
                                       const gfx::Size& dimensions,
                                       uint32 texture_target) = 0;

    
    virtual void DismissPictureBuffer(int32 picture_buffer_id) = 0;

    
    virtual void PictureReady(const Picture& picture) = 0;

    
    
    virtual void NotifyEndOfBitstreamBuffer(int32 bitstream_buffer_id) = 0;

    
    virtual void NotifyFlushDone() = 0;

    
    virtual void NotifyResetDone() = 0;

    
    
    
    virtual void NotifyError(Error error) = 0;

   protected:
    virtual ~Client() {}
  };

  

  
  
  
  
  
  
  
  virtual bool Initialize(VideoCodecProfile profile, Client* client) = 0;

  
  
  
  
  
  virtual void Decode(const BitstreamBuffer& bitstream_buffer) = 0;

  
  
  
  
  
  
  
  
  virtual void AssignPictureBuffers(
      const std::vector<PictureBuffer>& buffers) = 0;

  
  
  
  
  
  
  virtual void ReusePictureBuffer(int32 picture_buffer_id) = 0;

  
  
  
  virtual void Flush() = 0;

  
  
  
  
  virtual void Reset() = 0;

  
  
  
  
  
  virtual void Destroy() = 0;

  
  
  
  
  
  
  
  
  
  virtual bool CanDecodeOnIOThread();

 protected:
  
  
  virtual ~VideoDecodeAccelerator();
};

}  

namespace base {

template <class T>
struct DefaultDeleter;

template <>
struct MEDIA_EXPORT DefaultDeleter<media::VideoDecodeAccelerator> {
 public:
  void operator()(void* video_decode_accelerator) const;
};

}  

#endif  
