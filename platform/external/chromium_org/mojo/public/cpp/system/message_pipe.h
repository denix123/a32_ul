// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_SYSTEM_MESSAGE_PIPE_H_
#define MOJO_PUBLIC_CPP_SYSTEM_MESSAGE_PIPE_H_

#include <assert.h>

#include "mojo/public/c/system/message_pipe.h"
#include "mojo/public/cpp/system/handle.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {


class MessagePipeHandle : public Handle {
 public:
  MessagePipeHandle() {}
  explicit MessagePipeHandle(MojoHandle value) : Handle(value) {}

  
};

MOJO_COMPILE_ASSERT(sizeof(MessagePipeHandle) == sizeof(Handle),
                    bad_size_for_cpp_MessagePipeHandle);

typedef ScopedHandleBase<MessagePipeHandle> ScopedMessagePipeHandle;
MOJO_COMPILE_ASSERT(sizeof(ScopedMessagePipeHandle) ==
                        sizeof(MessagePipeHandle),
                    bad_size_for_cpp_ScopedMessagePipeHandle);

inline MojoResult CreateMessagePipe(const MojoCreateMessagePipeOptions* options,
                                    ScopedMessagePipeHandle* message_pipe0,
                                    ScopedMessagePipeHandle* message_pipe1) {
  assert(message_pipe0);
  assert(message_pipe1);
  MessagePipeHandle handle0;
  MessagePipeHandle handle1;
  MojoResult rv = MojoCreateMessagePipe(options,
                                        handle0.mutable_value(),
                                        handle1.mutable_value());
  
  
  message_pipe0->reset(handle0);
  message_pipe1->reset(handle1);
  return rv;
}

inline MojoResult WriteMessageRaw(MessagePipeHandle message_pipe,
                                  const void* bytes,
                                  uint32_t num_bytes,
                                  const MojoHandle* handles,
                                  uint32_t num_handles,
                                  MojoWriteMessageFlags flags) {
  return MojoWriteMessage(message_pipe.value(), bytes, num_bytes, handles,
                          num_handles, flags);
}

inline MojoResult ReadMessageRaw(MessagePipeHandle message_pipe,
                                 void* bytes,
                                 uint32_t* num_bytes,
                                 MojoHandle* handles,
                                 uint32_t* num_handles,
                                 MojoReadMessageFlags flags) {
  return MojoReadMessage(message_pipe.value(), bytes, num_bytes, handles,
                         num_handles, flags);
}

class MessagePipe {
 public:
  MessagePipe();
  explicit MessagePipe(const MojoCreateMessagePipeOptions& options);
  ~MessagePipe();

  ScopedMessagePipeHandle handle0;
  ScopedMessagePipeHandle handle1;
};

inline MessagePipe::MessagePipe() {
  MojoResult result MOJO_ALLOW_UNUSED =
      CreateMessagePipe(NULL, &handle0, &handle1);
  assert(result == MOJO_RESULT_OK);
}

inline MessagePipe::MessagePipe(const MojoCreateMessagePipeOptions& options) {
  MojoResult result MOJO_ALLOW_UNUSED =
      CreateMessagePipe(&options, &handle0, &handle1);
  assert(result == MOJO_RESULT_OK);
}

inline MessagePipe::~MessagePipe() {
}

}  

#endif  
