// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_IPC_MEDIA_MESSAGE_FIFO_H_
#define CHROMECAST_MEDIA_CMA_IPC_MEDIA_MESSAGE_FIFO_H_

#include <list>

#include "base/atomicops.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/logging.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"

namespace chromecast {
namespace media {
class MediaMemoryChunk;
class MediaMessage;
class MediaMessageFlag;

//   // (i.e. it was fully written), and fifo_feeder can then update
class MediaMessageFifo {
 public:
  
  
  
  MediaMessageFifo(scoped_ptr<MediaMemoryChunk> mem, bool init);
  ~MediaMessageFifo();

  
  
  
  void ObserveReadActivity(const base::Closure& read_event_cb);
  void ObserveWriteActivity(const base::Closure& write_event_cb);

  
  
  
  scoped_ptr<MediaMemoryChunk> ReserveMemory(size_t size);

  
  
  scoped_ptr<MediaMessage> Pop();

  
  void Flush();

 private:
  struct Descriptor {
    size_t size;
    size_t rd_offset;
    size_t wr_offset;

    
    int64 first_item;
  };

  
  size_t current_rd_offset() const;
  size_t current_wr_offset() const;
  size_t internal_rd_offset() const {
    DCHECK_LT(internal_rd_offset_, size_);
    return internal_rd_offset_;
  }
  size_t internal_wr_offset() const {
    DCHECK_LT(internal_wr_offset_, size_);
    return internal_wr_offset_;
  }

  
  
  scoped_ptr<MediaMemoryChunk> ReserveMemoryNoCheck(size_t size);

  
  // that has possibly been written.
  void OnWrMemoryReleased();

  
  
  void OnRdMemoryReleased();

  
  void CommitRead(size_t new_rd_offset);
  void CommitWrite(size_t new_wr_offset);
  void CommitInternalRead(size_t new_rd_offset);
  void CommitInternalWrite(size_t new_wr_offset);

  
  
  
  
  
  base::ThreadChecker thread_checker_;

  
  
  
  base::Closure read_event_cb_;
  base::Closure write_event_cb_;

  
  scoped_ptr<MediaMemoryChunk> mem_;

  
  
  
  size_t size_;

  
  
#if SIZE_MAX == UINT32_MAX
  typedef base::subtle::Atomic32 AtomicSize;
#elif SIZE_MAX == UINT64_MAX
  typedef base::subtle::Atomic64 AtomicSize;
#elif
#error "Unsupported size_t"
#endif
  AtomicSize* rd_offset_;
  AtomicSize* wr_offset_;

  
  
  // overwritten by the feeder.
  
  
  size_t internal_rd_offset_;
  size_t internal_wr_offset_;

  
  
  void* base_;

  // Protects the messages that are either being read or written.
  std::list<scoped_refptr<MediaMessageFlag> > rd_flags_;
  std::list<scoped_refptr<MediaMessageFlag> > wr_flags_;

  base::WeakPtrFactory<MediaMessageFifo> weak_factory_;
  base::WeakPtr<MediaMessageFifo> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(MediaMessageFifo);
};

}  
}  

#endif  
