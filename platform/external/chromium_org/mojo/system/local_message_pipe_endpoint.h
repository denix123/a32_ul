// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_LOCAL_MESSAGE_PIPE_ENDPOINT_H_
#define MOJO_SYSTEM_LOCAL_MESSAGE_PIPE_ENDPOINT_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "mojo/system/handle_signals_state.h"
#include "mojo/system/message_in_transit_queue.h"
#include "mojo/system/message_pipe_endpoint.h"
#include "mojo/system/system_impl_export.h"
#include "mojo/system/waiter_list.h"

namespace mojo {
namespace system {

class MOJO_SYSTEM_IMPL_EXPORT LocalMessagePipeEndpoint
    : public MessagePipeEndpoint {
 public:
  LocalMessagePipeEndpoint();
  virtual ~LocalMessagePipeEndpoint();

  
  virtual Type GetType() const OVERRIDE;
  virtual bool OnPeerClose() OVERRIDE;
  virtual void EnqueueMessage(scoped_ptr<MessageInTransit> message) OVERRIDE;

  
  
  virtual void Close() OVERRIDE;
  virtual void CancelAllWaiters() OVERRIDE;
  virtual MojoResult ReadMessage(UserPointer<void> bytes,
                                 UserPointer<uint32_t> num_bytes,
                                 DispatcherVector* dispatchers,
                                 uint32_t* num_dispatchers,
                                 MojoReadMessageFlags flags) OVERRIDE;
  virtual HandleSignalsState GetHandleSignalsState() const OVERRIDE;
  virtual MojoResult AddWaiter(Waiter* waiter,
                               MojoHandleSignals signals,
                               uint32_t context,
                               HandleSignalsState* signals_state) OVERRIDE;
  virtual void RemoveWaiter(Waiter* waiter,
                            HandleSignalsState* signals_state) OVERRIDE;

  
  MessageInTransitQueue* message_queue() { return &message_queue_; }

 private:
  bool is_open_;
  bool is_peer_open_;

  
  MessageInTransitQueue message_queue_;
  WaiterList waiter_list_;

  DISALLOW_COPY_AND_ASSIGN(LocalMessagePipeEndpoint);
};

}  
}  

#endif  
