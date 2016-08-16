// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_TRANSPORT_DATA_H_
#define MOJO_SYSTEM_TRANSPORT_DATA_H_

#include <stdint.h>

#include <vector>

#include "base/macros.h"
#include "base/memory/aligned_memory.h"
#include "base/memory/scoped_ptr.h"
#include "build/build_config.h"
#include "mojo/embedder/platform_handle.h"
#include "mojo/embedder/platform_handle_vector.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class Channel;

class MOJO_SYSTEM_IMPL_EXPORT TransportData {
 public:
  
  
  static const size_t kMaxSerializedDispatcherSize = 10000;

  
  
  static const size_t kMaxSerializedDispatcherPlatformHandles = 2;

  
  static const size_t kMaxBufferSize;

  
  static const size_t kMaxPlatformHandles;

  TransportData(scoped_ptr<DispatcherVector> dispatchers, Channel* channel);

#if defined(OS_POSIX)
  
  
  
  
  
  explicit TransportData(
      embedder::ScopedPlatformHandleVectorPtr platform_handles);
#endif

  ~TransportData();

  const void* buffer() const { return buffer_.get(); }
  void* buffer() { return buffer_.get(); }
  size_t buffer_size() const { return buffer_size_; }

  uint32_t platform_handle_table_offset() const {
    return header()->platform_handle_table_offset;
  }

  
  
  const embedder::PlatformHandleVector* platform_handles() const {
    return platform_handles_.get();
  }
  embedder::PlatformHandleVector* platform_handles() {
    return platform_handles_.get();
  }

  

  
  
  
  
  
  
  
  static const char* ValidateBuffer(size_t serialized_platform_handle_size,
                                    const void* buffer,
                                    size_t buffer_size);

  
  
  static void GetPlatformHandleTable(const void* transport_data_buffer,
                                     size_t* num_platform_handles,
                                     const void** platform_handle_table);

  
  
  
  static scoped_ptr<DispatcherVector> DeserializeDispatchers(
      const void* buffer,
      size_t buffer_size,
      embedder::ScopedPlatformHandleVectorPtr platform_handles,
      Channel* channel);

 private:
  
  
  struct PrivateStructForCompileAsserts;

  
  
  struct Header {
    uint32_t num_handles;
    
    uint32_t platform_handle_table_offset;
    uint32_t num_platform_handles;
    uint32_t unused;
  };

  struct HandleTableEntry {
    int32_t type;     
    uint32_t offset;  
    uint32_t size;    
    uint32_t unused;
  };

  const Header* header() const {
    return reinterpret_cast<const Header*>(buffer_.get());
  }

  size_t buffer_size_;
  scoped_ptr<char, base::AlignedFreeDeleter> buffer_;  

  
  
  
  
  embedder::ScopedPlatformHandleVectorPtr platform_handles_;

  DISALLOW_COPY_AND_ASSIGN(TransportData);
};

}  
}  

#endif  
