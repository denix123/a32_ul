// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_CLIENT_MAPPED_MEMORY_H_
#define GPU_COMMAND_BUFFER_CLIENT_MAPPED_MEMORY_H_

#include <stdint.h>

#include "base/bind.h"
#include "base/macros.h"
#include "base/memory/scoped_vector.h"
#include "gpu/command_buffer/client/fenced_allocator.h"
#include "gpu/command_buffer/common/buffer.h"
#include "gpu/gpu_export.h"

namespace gpu {

class CommandBufferHelper;

class GPU_EXPORT MemoryChunk {
 public:
  MemoryChunk(int32_t shm_id,
              scoped_refptr<gpu::Buffer> shm,
              CommandBufferHelper* helper,
              const base::Closure& poll_callback);
  ~MemoryChunk();

  
  unsigned int GetLargestFreeSizeWithoutWaiting() {
    return allocator_.GetLargestFreeSize();
  }

  
  
  unsigned int GetLargestFreeSizeWithWaiting() {
    return allocator_.GetLargestFreeOrPendingSize();
  }

  
  unsigned int GetSize() const {
    return static_cast<unsigned int>(shm_->size());
  }

  
  int32_t shm_id() const {
    return shm_id_;
  }

  
  
  
  
  
  
  
  
  
  
  void* Alloc(unsigned int size) {
    return allocator_.Alloc(size);
  }

  
  
  unsigned int GetOffset(void* pointer) {
    return allocator_.GetOffset(pointer);
  }

  
  
  
  
  void Free(void* pointer) {
    allocator_.Free(pointer);
  }

  
  
  
  
  
  
  void FreePendingToken(void* pointer, unsigned int token) {
    allocator_.FreePendingToken(pointer, token);
  }

  
  void FreeUnused() {
    allocator_.FreeUnused();
  }

  
  bool IsInChunk(void* pointer) const {
    return pointer >= shm_->memory() &&
           pointer <
               reinterpret_cast<const int8_t*>(shm_->memory()) + shm_->size();
  }

  
  bool InUse() {
    return allocator_.InUse();
  }

  size_t bytes_in_use() const {
    return allocator_.bytes_in_use();
  }

 private:
  int32_t shm_id_;
  scoped_refptr<gpu::Buffer> shm_;
  FencedAllocatorWrapper allocator_;

  DISALLOW_COPY_AND_ASSIGN(MemoryChunk);
};

class GPU_EXPORT MappedMemoryManager {
 public:
  enum MemoryLimit {
    kNoLimit = 0,
  };

  
  
  MappedMemoryManager(CommandBufferHelper* helper,
                      const base::Closure& poll_callback,
                      size_t unused_memory_reclaim_limit);

  ~MappedMemoryManager();

  unsigned int chunk_size_multiple() const {
    return chunk_size_multiple_;
  }

  void set_chunk_size_multiple(unsigned int multiple) {
    chunk_size_multiple_ = multiple;
  }

  
  
  
  
  
  
  
  void* Alloc(
      unsigned int size, int32_t* shm_id, unsigned int* shm_offset);

  
  
  
  
  void Free(void* pointer);

  
  
  
  
  
  
  void FreePendingToken(void* pointer, int32_t token);

  
  void FreeUnused();

  
  size_t num_chunks() const {
    return chunks_.size();
  }

  size_t bytes_in_use() const {
    size_t bytes_in_use = 0;
    for (size_t ii = 0; ii < chunks_.size(); ++ii) {
      MemoryChunk* chunk = chunks_[ii];
      bytes_in_use += chunk->bytes_in_use();
    }
    return bytes_in_use;
  }

  
  size_t allocated_memory() const {
    return allocated_memory_;
  }

 private:
  typedef ScopedVector<MemoryChunk> MemoryChunkVector;

  
  unsigned int chunk_size_multiple_;
  CommandBufferHelper* helper_;
  base::Closure poll_callback_;
  MemoryChunkVector chunks_;
  size_t allocated_memory_;
  size_t max_free_bytes_;

  DISALLOW_COPY_AND_ASSIGN(MappedMemoryManager);
};

}  

#endif  

