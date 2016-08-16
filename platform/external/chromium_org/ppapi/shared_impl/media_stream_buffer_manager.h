// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_SHARED_IMPL_MEDIA_STREAM_BUFFER_MANAGER_H_
#define PPAPI_SHARED_IMPL_MEDIA_STREAM_BUFFER_MANAGER_H_

#include <deque>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory.h"
#include "ppapi/shared_impl/ppapi_shared_export.h"

namespace ppapi {

union MediaStreamBuffer;

class PPAPI_SHARED_EXPORT MediaStreamBufferManager {
 public:
  class PPAPI_SHARED_EXPORT Delegate {
   public:
    virtual ~Delegate();
    
    virtual void OnNewBufferEnqueued();
  };

  
  
  explicit MediaStreamBufferManager(Delegate* delegate);

  ~MediaStreamBufferManager();

  int32_t number_of_buffers() const { return number_of_buffers_; }

  int32_t buffer_size() const { return buffer_size_; }

  
  bool SetBuffers(int32_t number_of_buffers,
                  int32_t buffer_size,
                  scoped_ptr<base::SharedMemory> shm,
                  bool enqueue_all_buffers);

  
  int32_t DequeueBuffer();

  
  std::vector<int32_t> DequeueBuffers();

  
  void EnqueueBuffer(int32_t index);

  
  MediaStreamBuffer* GetBufferPointer(int32_t index);

 private:
  Delegate* delegate_;

  
  std::deque<int32_t> buffer_queue_;

  
  std::vector<MediaStreamBuffer*> buffers_;

  
  int32_t buffer_size_;

  
  int32_t number_of_buffers_;

  
  scoped_ptr<base::SharedMemory> shm_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamBufferManager);
};

}  

#endif  
