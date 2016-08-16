// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_LOCAL_DATA_PIPE_H_
#define MOJO_SYSTEM_LOCAL_DATA_PIPE_H_

#include "base/macros.h"
#include "base/memory/aligned_memory.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/system/data_pipe.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class MOJO_SYSTEM_IMPL_EXPORT LocalDataPipe : public DataPipe {
 public:
  
  
  
  explicit LocalDataPipe(const MojoCreateDataPipeOptions& validated_options);

 private:
  friend class base::RefCountedThreadSafe<LocalDataPipe>;
  virtual ~LocalDataPipe();

  
  virtual void ProducerCloseImplNoLock() OVERRIDE;
  virtual MojoResult ProducerWriteDataImplNoLock(
      UserPointer<const void> elements,
      UserPointer<uint32_t> num_bytes,
      uint32_t max_num_bytes_to_write,
      uint32_t min_num_bytes_to_write) OVERRIDE;
  virtual MojoResult ProducerBeginWriteDataImplNoLock(
      UserPointer<void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      uint32_t min_num_bytes_to_write) OVERRIDE;
  virtual MojoResult ProducerEndWriteDataImplNoLock(
      uint32_t num_bytes_written) OVERRIDE;
  virtual HandleSignalsState ProducerGetHandleSignalsStateImplNoLock()
      const OVERRIDE;
  virtual void ConsumerCloseImplNoLock() OVERRIDE;
  virtual MojoResult ConsumerReadDataImplNoLock(
      UserPointer<void> elements,
      UserPointer<uint32_t> num_bytes,
      uint32_t max_num_bytes_to_read,
      uint32_t min_num_bytes_to_read) OVERRIDE;
  virtual MojoResult ConsumerDiscardDataImplNoLock(
      UserPointer<uint32_t> num_bytes,
      uint32_t max_num_bytes_to_discard,
      uint32_t min_num_bytes_to_discard) OVERRIDE;
  virtual MojoResult ConsumerQueryDataImplNoLock(
      UserPointer<uint32_t> num_bytes) OVERRIDE;
  virtual MojoResult ConsumerBeginReadDataImplNoLock(
      UserPointer<const void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      uint32_t min_num_bytes_to_read) OVERRIDE;
  virtual MojoResult ConsumerEndReadDataImplNoLock(
      uint32_t num_bytes_read) OVERRIDE;
  virtual HandleSignalsState ConsumerGetHandleSignalsStateImplNoLock()
      const OVERRIDE;

  void EnsureBufferNoLock();
  void DestroyBufferNoLock();

  
  
  size_t GetMaxNumBytesToWriteNoLock();
  size_t GetMaxNumBytesToReadNoLock();

  
  
  void MarkDataAsConsumedNoLock(size_t num_bytes);

  
  scoped_ptr<char, base::AlignedFreeDeleter> buffer_;
  
  size_t start_index_;
  size_t current_num_bytes_;

  DISALLOW_COPY_AND_ASSIGN(LocalDataPipe);
};

}  
}  

#endif  
