// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MESSAGE_PIPE_H_
#define MOJO_SYSTEM_MESSAGE_PIPE_H_

#include <stdint.h>

#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "mojo/public/c/system/message_pipe.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/handle_signals_state.h"
#include "mojo/system/memory.h"
#include "mojo/system/message_in_transit.h"
#include "mojo/system/message_pipe_endpoint.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class ChannelEndpoint;
class Waiter;

class MOJO_SYSTEM_IMPL_EXPORT MessagePipe
    : public base::RefCountedThreadSafe<MessagePipe> {
 public:
  
  static MessagePipe* CreateLocalLocal();

  
  
  
  static MessagePipe* CreateLocalProxy(
      scoped_refptr<ChannelEndpoint>* channel_endpoint);

  
  
  
  
  
  
  static MessagePipe* CreateProxyLocal(
      scoped_refptr<ChannelEndpoint>* channel_endpoint);

  
  static unsigned GetPeerPort(unsigned port);

  
  MessagePipeEndpoint::Type GetType(unsigned port);

  
  
  void CancelAllWaiters(unsigned port);
  void Close(unsigned port);
  
  
  MojoResult WriteMessage(unsigned port,
                          UserPointer<const void> bytes,
                          uint32_t num_bytes,
                          std::vector<DispatcherTransport>* transports,
                          MojoWriteMessageFlags flags);
  MojoResult ReadMessage(unsigned port,
                         UserPointer<void> bytes,
                         UserPointer<uint32_t> num_bytes,
                         DispatcherVector* dispatchers,
                         uint32_t* num_dispatchers,
                         MojoReadMessageFlags flags);
  HandleSignalsState GetHandleSignalsState(unsigned port) const;
  MojoResult AddWaiter(unsigned port,
                       Waiter* waiter,
                       MojoHandleSignals signals,
                       uint32_t context,
                       HandleSignalsState* signals_state);
  void RemoveWaiter(unsigned port,
                    Waiter* waiter,
                    HandleSignalsState* signals_state);

  
  
  scoped_refptr<ChannelEndpoint> ConvertLocalToProxy(unsigned port);

  
  
  
  MojoResult EnqueueMessage(unsigned port,
                            scoped_ptr<MessageInTransit> message);

  
  
  void OnRemove(unsigned port);

 private:
  MessagePipe();

  friend class base::RefCountedThreadSafe<MessagePipe>;
  virtual ~MessagePipe();

  
  
  
  MojoResult EnqueueMessageInternal(
      unsigned port,
      scoped_ptr<MessageInTransit> message,
      std::vector<DispatcherTransport>* transports);

  
  MojoResult AttachTransportsNoLock(
      unsigned port,
      MessageInTransit* message,
      std::vector<DispatcherTransport>* transports);

  
  
  MojoResult HandleControlMessage(unsigned port,
                                  scoped_ptr<MessageInTransit> message);

  base::Lock lock_;  
  scoped_ptr<MessagePipeEndpoint> endpoints_[2];

  DISALLOW_COPY_AND_ASSIGN(MessagePipe);
};

}  
}  

#endif  
