// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_IPC_MEDIA_MEMORY_CHUNK_H_
#define CHROMECAST_MEDIA_CMA_IPC_MEDIA_MEMORY_CHUNK_H_

#include "base/basictypes.h"

namespace chromecast {
namespace media {

class MediaMemoryChunk {
 public:
  virtual ~MediaMemoryChunk();

  
  virtual void* data() const = 0;

  
  virtual size_t size() const = 0;

  
  
  
  
  virtual bool valid() const = 0;
};

}  
}  

#endif  
