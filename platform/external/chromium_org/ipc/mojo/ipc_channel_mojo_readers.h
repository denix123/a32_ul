// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_MOJO_IPC_CHANNEL_MOJO_READERS_H_
#define IPC_MOJO_IPC_CHANNEL_MOJO_READERS_H_

#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "ipc/mojo/ipc_message_pipe_reader.h"
#include "mojo/public/cpp/system/core.h"

namespace mojo {
namespace embedder {
struct ChannelInfo;
}
}

namespace IPC {

class ChannelMojo;
class Message;

namespace internal {

class MessageReader : public MessagePipeReader {
 public:
  MessageReader(mojo::ScopedMessagePipeHandle pipe, ChannelMojo* owner);

  bool Send(scoped_ptr<Message> message);

  
  virtual void OnMessageReceived() OVERRIDE;
  virtual void OnPipeClosed() OVERRIDE;
  virtual void OnPipeError(MojoResult error) OVERRIDE;

 private:
  ChannelMojo* owner_;

  DISALLOW_COPY_AND_ASSIGN(MessageReader);
};

class ControlReader : public MessagePipeReader {
 public:
  ControlReader(mojo::ScopedMessagePipeHandle pipe, ChannelMojo* owner);

  virtual bool Connect();

  
  virtual void OnPipeClosed() OVERRIDE;
  virtual void OnPipeError(MojoResult error) OVERRIDE;

 protected:
  ChannelMojo* owner_;

  DISALLOW_COPY_AND_ASSIGN(ControlReader);
};

class ServerControlReader : public ControlReader {
 public:
  ServerControlReader(mojo::ScopedMessagePipeHandle pipe, ChannelMojo* owner);
  virtual ~ServerControlReader();

  
  virtual bool Connect() OVERRIDE;

  
  virtual void OnMessageReceived() OVERRIDE;

 private:
  MojoResult SendHelloRequest();
  MojoResult RespondHelloResponse();

  mojo::ScopedMessagePipeHandle message_pipe_;

  DISALLOW_COPY_AND_ASSIGN(ServerControlReader);
};

class ClientControlReader : public ControlReader {
 public:
  ClientControlReader(mojo::ScopedMessagePipeHandle pipe, ChannelMojo* owner);

  
  virtual void OnMessageReceived() OVERRIDE;

 private:
  MojoResult RespondHelloRequest(MojoHandle message_channel);

  DISALLOW_COPY_AND_ASSIGN(ClientControlReader);
};

}  
}  

#endif  
