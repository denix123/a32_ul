// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_CLIENT_GPU_MEMORY_BUFFER_IMPL_H_
#define CONTENT_COMMON_GPU_CLIENT_GPU_MEMORY_BUFFER_IMPL_H_

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gfx/size.h"

namespace content {

class GpuMemoryBufferImpl : public gfx::GpuMemoryBuffer {
 public:
  typedef base::Callback<void(scoped_ptr<GpuMemoryBufferImpl> buffer)>
      CreationCallback;
  typedef base::Callback<void(const gfx::GpuMemoryBufferHandle& handle)>
      AllocationCallback;
  typedef base::Closure DestructionCallback;

  virtual ~GpuMemoryBufferImpl();

  
  
  static void Create(const gfx::Size& size,
                     unsigned internalformat,
                     unsigned usage,
                     int client_id,
                     const CreationCallback& callback);

  
  
  
  static void AllocateForChildProcess(const gfx::Size& size,
                                      unsigned internalformat,
                                      unsigned usage,
                                      base::ProcessHandle child_process,
                                      int child_client_id,
                                      const AllocationCallback& callback);

  
  static void DeletedByChildProcess(gfx::GpuMemoryBufferType type,
                                    const gfx::GpuMemoryBufferId& id,
                                    base::ProcessHandle child_process);

  
  
  
  
  static scoped_ptr<GpuMemoryBufferImpl> CreateFromHandle(
      const gfx::GpuMemoryBufferHandle& handle,
      const gfx::Size& size,
      unsigned internalformat,
      const DestructionCallback& callback);

  
  static bool IsFormatValid(unsigned internalformat);

  
  static bool IsUsageValid(unsigned usage);

  
  
  static size_t BytesPerPixel(unsigned internalformat);

  
  virtual bool IsMapped() const OVERRIDE;

 protected:
  GpuMemoryBufferImpl(const gfx::Size& size,
                      unsigned internalformat,
                      const DestructionCallback& callback);

  const gfx::Size size_;
  const unsigned internalformat_;
  const DestructionCallback callback_;
  bool mapped_;

  DISALLOW_COPY_AND_ASSIGN(GpuMemoryBufferImpl);
};

}  

#endif  
