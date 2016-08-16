// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_SHARED_BUFFER_DISPATCHER_H_
#define MOJO_SYSTEM_SHARED_BUFFER_DISPATCHER_H_

#include "base/macros.h"
#include "mojo/embedder/platform_shared_buffer.h"
#include "mojo/system/memory.h"
#include "mojo/system/simple_dispatcher.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {

namespace embedder {
class PlatformSupport;
}

namespace system {

class MOJO_SYSTEM_IMPL_EXPORT SharedBufferDispatcher : public SimpleDispatcher {
 public:
  
  
  
  static const MojoCreateSharedBufferOptions kDefaultCreateOptions;

  
  
  
  // |MojoCreateSharedBufferOptions| and will be entirely overwritten on success
  // (it may be partly overwritten on failure).
  static MojoResult ValidateCreateOptions(
      UserPointer<const MojoCreateSharedBufferOptions> in_options,
      MojoCreateSharedBufferOptions* out_options);

  
  
  static MojoResult Create(
      embedder::PlatformSupport* platform_support,
      const MojoCreateSharedBufferOptions& validated_options,
      uint64_t num_bytes,
      scoped_refptr<SharedBufferDispatcher>* result);

  
  virtual Type GetType() const OVERRIDE;

  
  
  static scoped_refptr<SharedBufferDispatcher> Deserialize(
      Channel* channel,
      const void* source,
      size_t size,
      embedder::PlatformHandleVector* platform_handles);

 private:
  explicit SharedBufferDispatcher(
      scoped_refptr<embedder::PlatformSharedBuffer> shared_buffer_);
  virtual ~SharedBufferDispatcher();

  
  
  
  
  // entirely overwritten on success (it may be partly overwritten on failure).
  static MojoResult ValidateDuplicateOptions(
      UserPointer<const MojoDuplicateBufferHandleOptions> in_options,
      MojoDuplicateBufferHandleOptions* out_options);

  
  virtual void CloseImplNoLock() OVERRIDE;
  virtual scoped_refptr<Dispatcher>
      CreateEquivalentDispatcherAndCloseImplNoLock() OVERRIDE;
  virtual MojoResult DuplicateBufferHandleImplNoLock(
      UserPointer<const MojoDuplicateBufferHandleOptions> options,
      scoped_refptr<Dispatcher>* new_dispatcher) OVERRIDE;
  virtual MojoResult MapBufferImplNoLock(
      uint64_t offset,
      uint64_t num_bytes,
      MojoMapBufferFlags flags,
      scoped_ptr<embedder::PlatformSharedBufferMapping>* mapping) OVERRIDE;
  virtual void StartSerializeImplNoLock(Channel* channel,
                                        size_t* max_size,
                                        size_t* max_platform_handles) OVERRIDE;
  virtual bool EndSerializeAndCloseImplNoLock(
      Channel* channel,
      void* destination,
      size_t* actual_size,
      embedder::PlatformHandleVector* platform_handles) OVERRIDE;

  scoped_refptr<embedder::PlatformSharedBuffer> shared_buffer_;

  DISALLOW_COPY_AND_ASSIGN(SharedBufferDispatcher);
};

}  
}  

#endif  
