// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_MESSAGE_PIPE_READER_H_
#define IPC_IPC_MESSAGE_PIPE_READER_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "mojo/public/c/environment/async_waiter.h"
#include "mojo/public/cpp/system/core.h"

namespace IPC {
namespace internal {

class MessagePipeReader {
 public:
  
  
  class DelayedDeleter {
   public:
    typedef base::DefaultDeleter<MessagePipeReader> DefaultType;

    static void DeleteNow(MessagePipeReader* ptr) { delete ptr; }

    DelayedDeleter() {}
    DelayedDeleter(const DefaultType&) {}
    DelayedDeleter& operator=(const DefaultType&) { return *this; }

    void operator()(MessagePipeReader* ptr) const;
  };

  explicit MessagePipeReader(mojo::ScopedMessagePipeHandle handle);
  virtual ~MessagePipeReader();

  MojoHandle handle() const { return pipe_.get().value(); }

  
  const std::vector<char>& data_buffer() const {
    return data_buffer_;
  }

  
  
  void TakeHandleBuffer(std::vector<MojoHandle>* handle_buffer) {
    handle_buffer_.swap(*handle_buffer);
  }

  
  void Close();
  
  void CloseWithError(MojoResult error);
  
  bool IsValid() { return pipe_.is_valid(); }

  
  
  
  
  virtual void OnMessageReceived() = 0;
  virtual void OnPipeClosed() = 0;
  virtual void OnPipeError(MojoResult error) = 0;

 private:
  static void InvokePipeIsReady(void* closure, MojoResult result);

  MojoResult ReadMessageBytes();
  void PipeIsReady(MojoResult wait_result);
  void StartWaiting();
  void StopWaiting();

  std::vector<char>  data_buffer_;
  std::vector<MojoHandle> handle_buffer_;
  MojoAsyncWaitID pipe_wait_id_;
  mojo::ScopedMessagePipeHandle pipe_;

  DISALLOW_COPY_AND_ASSIGN(MessagePipeReader);
};

}  
}  

#endif  
