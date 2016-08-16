// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_CHANNEL_ENDPOINT_H_
#define MOJO_SYSTEM_CHANNEL_ENDPOINT_H_

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "mojo/system/message_in_transit.h"
#include "mojo/system/message_in_transit_queue.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class Channel;
class MessagePipe;

//         are thus written to the *peer* of this port.
//     if messages written to it (via some |MessagePipeDispatcher|, to which
//         no longer be written to it.
class MOJO_SYSTEM_IMPL_EXPORT ChannelEndpoint
    : public base::RefCountedThreadSafe<ChannelEndpoint> {
 public:
  
  ChannelEndpoint(MessagePipe* message_pipe, unsigned port);

  
  
  
  void TakeMessages(MessageInTransitQueue* message_queue);

  

  
  
  
  bool EnqueueMessage(scoped_ptr<MessageInTransit> message);

  void DetachFromMessagePipe();

  

  
  void AttachToChannel(Channel* channel, MessageInTransit::EndpointId local_id);

  
  void Run(MessageInTransit::EndpointId remote_id);

  
  void DetachFromChannel();

 private:
  enum State {
    
    STATE_NORMAL,
    
    
    STATE_WAIT_LOCAL_DETACH,
    
    
    STATE_WAIT_REMOTE_REMOVE_ACK,
  };

  
  
  friend class Channel;

  friend class base::RefCountedThreadSafe<ChannelEndpoint>;
  ~ChannelEndpoint();

  
  bool WriteMessageNoLock(scoped_ptr<MessageInTransit> message);

  
  State state_;
  
  scoped_refptr<MessagePipe> message_pipe_;
  unsigned port_;

  
  
  base::Lock lock_;

  
  
  Channel* channel_;
  MessageInTransit::EndpointId local_id_;
  MessageInTransit::EndpointId remote_id_;

  
  
  MessageInTransitQueue paused_message_queue_;

  DISALLOW_COPY_AND_ASSIGN(ChannelEndpoint);
};

}  
}  

#endif  
