// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_DECODER_BUFFER_BASE_H_
#define CHROMECAST_MEDIA_CMA_BASE_DECODER_BUFFER_BASE_H_

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"

namespace media {
class DecryptConfig;
}

namespace chromecast {
namespace media {

class DecoderBufferBase
    : public base::RefCountedThreadSafe<DecoderBufferBase> {
 public:
  DecoderBufferBase();

  
  virtual base::TimeDelta timestamp() const = 0;

  
  virtual const uint8* data() const = 0;
  virtual uint8* writable_data() const = 0;

  
  virtual int data_size() const = 0;

  
  
  virtual const ::media::DecryptConfig* decrypt_config() const = 0;

  
  
  virtual bool end_of_stream() const = 0;

 protected:
  friend class base::RefCountedThreadSafe<DecoderBufferBase>;
  virtual ~DecoderBufferBase();

 private:
  DISALLOW_COPY_AND_ASSIGN(DecoderBufferBase);
};

}  
}  

#endif  
