// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MESSAGE_PIPE_DISPATCHER_H_
#define MOJO_SYSTEM_MESSAGE_PIPE_DISPATCHER_H_

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/memory.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class ChannelEndpoint;
class MessagePipe;
class MessagePipeDispatcherTransport;

class MOJO_SYSTEM_IMPL_EXPORT MessagePipeDispatcher : public Dispatcher {
 public:
  
  
  
  static const MojoCreateMessagePipeOptions kDefaultCreateOptions;

  MessagePipeDispatcher(
      const MojoCreateMessagePipeOptions& );

  
  
  
  // |MojoCreateMessagePipeOptions| and will be entirely overwritten on success
  // (it may be partly overwritten on failure).
  static MojoResult ValidateCreateOptions(
      UserPointer<const MojoCreateMessagePipeOptions> in_options,
      MojoCreateMessagePipeOptions* out_options);

  
  void Init(scoped_refptr<MessagePipe> message_pipe, unsigned port);

  
  virtual Type GetType() const OVERRIDE;

  
  
  
  
  
  static scoped_refptr<MessagePipeDispatcher> CreateRemoteMessagePipe(
      scoped_refptr<ChannelEndpoint>* channel_endpoint);

  
  
  static scoped_refptr<MessagePipeDispatcher> Deserialize(Channel* channel,
                                                          const void* source,
                                                          size_t size);

 private:
  friend class MessagePipeDispatcherTransport;

  virtual ~MessagePipeDispatcher();

  
  
  
  
  MessagePipe* GetMessagePipeNoLock() const;
  
  unsigned GetPortNoLock() const;

  
  virtual void CancelAllWaitersNoLock() OVERRIDE;
  virtual void CloseImplNoLock() OVERRIDE;
  virtual scoped_refptr<Dispatcher>
      CreateEquivalentDispatcherAndCloseImplNoLock() OVERRIDE;
  virtual MojoResult WriteMessageImplNoLock(
      UserPointer<const void> bytes,
      uint32_t num_bytes,
      std::vector<DispatcherTransport>* transports,
      MojoWriteMessageFlags flags) OVERRIDE;
  virtual MojoResult ReadMessageImplNoLock(UserPointer<void> bytes,
                                           UserPointer<uint32_t> num_bytes,
                                           DispatcherVector* dispatchers,
                                           uint32_t* num_dispatchers,
                                           MojoReadMessageFlags flags) OVERRIDE;
  virtual HandleSignalsState GetHandleSignalsStateImplNoLock() const OVERRIDE;
  virtual MojoResult AddWaiterImplNoLock(
      Waiter* waiter,
      MojoHandleSignals signals,
      uint32_t context,
      HandleSignalsState* signals_state) OVERRIDE;
  virtual void RemoveWaiterImplNoLock(
      Waiter* waiter,
      HandleSignalsState* signals_state) OVERRIDE;
  virtual void StartSerializeImplNoLock(Channel* channel,
                                        size_t* max_size,
                                        size_t* max_platform_handles) OVERRIDE;
  virtual bool EndSerializeAndCloseImplNoLock(
      Channel* channel,
      void* destination,
      size_t* actual_size,
      embedder::PlatformHandleVector* platform_handles) OVERRIDE;

  
  scoped_refptr<MessagePipe> message_pipe_;  
  unsigned port_;

  DISALLOW_COPY_AND_ASSIGN(MessagePipeDispatcher);
};

class MessagePipeDispatcherTransport : public DispatcherTransport {
 public:
  explicit MessagePipeDispatcherTransport(DispatcherTransport transport);

  MessagePipe* GetMessagePipe() {
    return message_pipe_dispatcher()->GetMessagePipeNoLock();
  }
  unsigned GetPort() { return message_pipe_dispatcher()->GetPortNoLock(); }

 private:
  MessagePipeDispatcher* message_pipe_dispatcher() {
    return static_cast<MessagePipeDispatcher*>(dispatcher());
  }

  
};

}  
}  

#endif  
