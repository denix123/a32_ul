// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_RAW_CHANNEL_H_
#define MOJO_SYSTEM_RAW_CHANNEL_H_

#include <deque>
#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "mojo/embedder/platform_handle_vector.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "mojo/system/constants.h"
#include "mojo/system/message_in_transit.h"
#include "mojo/system/system_impl_export.h"

namespace base {
class MessageLoopForIO;
}

namespace mojo {
namespace system {

//    view of the caller. If necessary, messages are queued (to be written on
class MOJO_SYSTEM_IMPL_EXPORT RawChannel {
 public:
  virtual ~RawChannel();

  
  
  class MOJO_SYSTEM_IMPL_EXPORT Delegate {
   public:
    enum Error {
      
      ERROR_READ_SHUTDOWN,
      
      
      ERROR_READ_BROKEN,
      
      ERROR_READ_BAD_MESSAGE,
      
      ERROR_READ_UNKNOWN,
      
      ERROR_WRITE
    };

    
    
    virtual void OnReadMessage(
        const MessageInTransit::View& message_view,
        embedder::ScopedPlatformHandleVectorPtr platform_handles) = 0;

    
    
    
    
    
    
    virtual void OnError(Error error) = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  
  static scoped_ptr<RawChannel> Create(embedder::ScopedPlatformHandle handle);

  
  
  
  
  
  bool Init(Delegate* delegate);

  
  void Shutdown();

  // Writes the given message (or schedules it to be written). |message| must
  
  
  
  bool WriteMessage(scoped_ptr<MessageInTransit> message);

  // Returns true if the write buffer is empty (i.e., all messages written using
  
  
  
  bool IsWriteBufferEmpty();

  
  
  
  virtual size_t GetSerializedPlatformHandleSize() const = 0;

 protected:
  
  enum IOResult {
    IO_SUCCEEDED,
    
    IO_FAILED_SHUTDOWN,
    
    IO_FAILED_BROKEN,
    
    IO_FAILED_UNKNOWN,
    IO_PENDING
  };

  class MOJO_SYSTEM_IMPL_EXPORT ReadBuffer {
   public:
    ReadBuffer();
    ~ReadBuffer();

    void GetBuffer(char** addr, size_t* size);

   private:
    friend class RawChannel;

    
    
    
    
    std::vector<char> buffer_;
    size_t num_valid_bytes_;

    DISALLOW_COPY_AND_ASSIGN(ReadBuffer);
  };

  class MOJO_SYSTEM_IMPL_EXPORT WriteBuffer {
   public:
    struct Buffer {
      const char* addr;
      size_t size;
    };

    explicit WriteBuffer(size_t serialized_platform_handle_size);
    ~WriteBuffer();

    
    
    bool HavePlatformHandlesToSend() const;
    
    
    
    
    
    
    // handles have been sent, the message data should be written next (see
    
    void GetPlatformHandlesToSend(size_t* num_platform_handles,
                                  embedder::PlatformHandle** platform_handles,
                                  void** serialization_data);

    // Gets buffers to be written. These buffers will always come from the front
    // of |message_queue_|. Once they are completely written, the front
    
    
    void GetBuffers(std::vector<Buffer>* buffers) const;

   private:
    friend class RawChannel;

    const size_t serialized_platform_handle_size_;

    
    
    std::deque<MessageInTransit*> message_queue_;
    
    
    
    size_t platform_handles_offset_;
    
    
    
    size_t data_offset_;

    DISALLOW_COPY_AND_ASSIGN(WriteBuffer);
  };

  RawChannel();

  
  
  void OnReadCompleted(IOResult io_result, size_t bytes_read);
  
  
  void OnWriteCompleted(IOResult io_result,
                        size_t platform_handles_written,
                        size_t bytes_written);

  base::MessageLoopForIO* message_loop_for_io() { return message_loop_for_io_; }
  base::Lock& write_lock() { return write_lock_; }

  
  ReadBuffer* read_buffer() { return read_buffer_.get(); }

  
  WriteBuffer* write_buffer_no_lock() {
    write_lock_.AssertAcquired();
    return write_buffer_.get();
  }

  
  
  
  virtual void EnqueueMessageNoLock(scoped_ptr<MessageInTransit> message);

  
  
  
  
  
  
  virtual bool OnReadMessageForRawChannel(
      const MessageInTransit::View& message_view);

  
  
  
  
  
  
  
  
  
  
  
  virtual IOResult Read(size_t* bytes_read) = 0;
  
  
  
  virtual IOResult ScheduleRead() = 0;

  
  
  
  
  
  virtual embedder::ScopedPlatformHandleVectorPtr GetReadPlatformHandles(
      size_t num_platform_handles,
      const void* platform_handle_table) = 0;

  
  
  
  
  
  
  
  
  
  // - |platform_handles_written| and |bytes_written| are untouched unless
  
  
  
  virtual IOResult WriteNoLock(size_t* platform_handles_written,
                               size_t* bytes_written) = 0;
  
  
  
  virtual IOResult ScheduleWriteNoLock() = 0;

  
  virtual bool OnInit() = 0;
  
  
  
  virtual void OnShutdownNoLock(scoped_ptr<ReadBuffer> read_buffer,
                                scoped_ptr<WriteBuffer> write_buffer) = 0;

 private:
  
  static Delegate::Error ReadIOResultToError(IOResult io_result);

  
  
  void CallOnError(Delegate::Error error);

  
  
  
  
  
  bool OnWriteCompletedNoLock(IOResult io_result,
                              size_t platform_handles_written,
                              size_t bytes_written);

  
  
  base::MessageLoopForIO* message_loop_for_io_;

  
  Delegate* delegate_;
  bool read_stopped_;
  scoped_ptr<ReadBuffer> read_buffer_;

  base::Lock write_lock_;  
  bool write_stopped_;
  scoped_ptr<WriteBuffer> write_buffer_;

  
  
  
  base::WeakPtrFactory<RawChannel> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(RawChannel);
};

}  
}  

#endif  
