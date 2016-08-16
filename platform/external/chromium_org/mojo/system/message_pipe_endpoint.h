// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MESSAGE_PIPE_ENDPOINT_H_
#define MOJO_SYSTEM_MESSAGE_PIPE_ENDPOINT_H_

#include <stdint.h>

#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/public/c/system/message_pipe.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/memory.h"
#include "mojo/system/message_in_transit.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class ChannelEndpoint;
class Waiter;

class MOJO_SYSTEM_IMPL_EXPORT MessagePipeEndpoint {
 public:
  virtual ~MessagePipeEndpoint() {}

  enum Type { kTypeLocal, kTypeProxy };
  virtual Type GetType() const = 0;

  
  
  virtual bool OnPeerClose() = 0;
  
  
  
  
  virtual void EnqueueMessage(scoped_ptr<MessageInTransit> message) = 0;

  
  
  
  
  
  
  
  
  virtual void Close();
  virtual void CancelAllWaiters();
  virtual MojoResult ReadMessage(UserPointer<void> bytes,
                                 UserPointer<uint32_t> num_bytes,
                                 DispatcherVector* dispatchers,
                                 uint32_t* num_dispatchers,
                                 MojoReadMessageFlags flags);
  virtual HandleSignalsState GetHandleSignalsState() const;
  virtual MojoResult AddWaiter(Waiter* waiter,
                               MojoHandleSignals signals,
                               uint32_t context,
                               HandleSignalsState* signals_state);
  virtual void RemoveWaiter(Waiter* waiter, HandleSignalsState* signals_state);

  
  
  
  virtual void Attach(ChannelEndpoint* channel_endpoint);

 protected:
  MessagePipeEndpoint() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(MessagePipeEndpoint);
};

}  
}  

#endif  
