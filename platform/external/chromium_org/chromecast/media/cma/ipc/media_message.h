// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_IPC_MEDIA_MESSAGE_H_
#define CHROMECAST_MEDIA_CMA_IPC_MEDIA_MESSAGE_H_

#include <stddef.h>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace chromecast {
namespace media {
class MediaMemoryChunk;

class MediaMessage {
 public:
  
  
  
  typedef base::Callback<scoped_ptr<MediaMemoryChunk>(size_t)>
      MemoryAllocatorCB;

  
  
  
  
  static scoped_ptr<MediaMessage> CreateDummyMessage(uint32 type);

  
  
  
  static scoped_ptr<MediaMessage> CreateMessage(
      uint32 type,
      const MemoryAllocatorCB& memory_allocator,
      size_t msg_content_capacity);

  
  
  static scoped_ptr<MediaMessage> CreateMessage(
      uint32 type,
      scoped_ptr<MediaMemoryChunk> mem);

  
  
  
  static scoped_ptr<MediaMessage> MapMessage(
      scoped_ptr<MediaMemoryChunk> mem);

  
  static size_t minimum_msg_size() {
    return offsetof(SerializedMsg, content);
  }

  ~MediaMessage();

  
  
  
  
  bool IsSerializedMsgAvailable() const;

  
  
  const void* msg() const { return msg_read_only_; }
  size_t size() const { return cached_msg_.header.size; }

  
  size_t actual_size() const {
    return minimum_msg_size() + cached_msg_.header.content_size;
  }

  
  size_t content_size() const { return cached_msg_.header.content_size; }

  
  uint32 type() const { return cached_msg_.header.type; }

  
  // Return true if the POD has been succesfully written.
  template<typename T> bool WritePod(T* const& pod);
  template<typename T> bool WritePod(const T& pod) {
    return WriteBuffer(&pod, sizeof(T));
  }

  
  bool WriteBuffer(const void* src, size_t size);

  
  template<typename T> bool ReadPod(T* pod) {
    return ReadBuffer(pod, sizeof(T));
  }

  
  
  bool ReadBuffer(void* dst, size_t size);

  
  
  const void* GetBuffer(size_t size);
  void* GetWritableBuffer(size_t size);

 private:
  MediaMessage(uint32 type, size_t msg_size);
  MediaMessage(uint32 type, scoped_ptr<MediaMemoryChunk> memory);
  MediaMessage(scoped_ptr<MediaMemoryChunk> memory);

  struct Header {
    
    uint32 size;
    
    uint32 type;
    
    uint32 content_size;
  };

  struct SerializedMsg {
    
    Header header;

    
    
    uint8 content;
  };

  
  
  
  bool is_dummy_msg_;

  
  
  
  
  SerializedMsg cached_msg_;
  Header* const cached_header_;

  SerializedMsg* msg_;
  SerializedMsg* msg_read_only_;

  
  
  
  scoped_ptr<MediaMemoryChunk> mem_;

  
  size_t rd_offset_;

  DISALLOW_COPY_AND_ASSIGN(MediaMessage);
};

}  
}  

#endif
