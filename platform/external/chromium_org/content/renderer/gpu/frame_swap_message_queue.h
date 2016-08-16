// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_GPU_FRAME_SWAP_MESSAGE_QUEUE_H_
#define CONTENT_RENDERER_GPU_FRAME_SWAP_MESSAGE_QUEUE_H_

#include <map>
#include <vector>

#include "base/auto_reset.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/synchronization/lock.h"
#include "cc/base/swap_promise.h"
#include "content/common/content_export.h"
#include "content/renderer/message_delivery_policy.h"

namespace IPC {
class Message;
};

namespace content {

class FrameSwapMessageSubQueue;

class CONTENT_EXPORT FrameSwapMessageQueue
    : public base::RefCountedThreadSafe<FrameSwapMessageQueue> {
 public:
  class CONTENT_EXPORT SendMessageScope {
   public:
    virtual ~SendMessageScope() {}
  };

  FrameSwapMessageQueue();

  
  
  
  
  
  
  
  void QueueMessageForFrame(MessageDeliveryPolicy policy,
                            int source_frame_number,
                            scoped_ptr<IPC::Message> msg,
                            bool* is_first);

  
  bool Empty() const;

  
  
  
  
  void DidSwap(int source_frame_number);

  
  
  
  
  
  
  
  
  void DidNotSwap(int source_frame_number,
                  cc::SwapPromise::DidNotSwapReason reason,
                  ScopedVector<IPC::Message>* messages);

  
  
  
  
  
  
  void DrainMessages(ScopedVector<IPC::Message>* messages);

  
  
  
  
  
  scoped_ptr<SendMessageScope> AcquireSendMessageScope();

  static void TransferMessages(ScopedVector<IPC::Message>& source,
                               std::vector<IPC::Message>* dest);

 private:
  friend class base::RefCountedThreadSafe<FrameSwapMessageQueue>;

  FrameSwapMessageSubQueue* GetSubQueue(MessageDeliveryPolicy policy);

  ~FrameSwapMessageQueue();

  mutable base::Lock lock_;
  scoped_ptr<FrameSwapMessageSubQueue> visual_state_queue_;
  scoped_ptr<FrameSwapMessageSubQueue> swap_queue_;
  ScopedVector<IPC::Message> next_drain_messages_;

  DISALLOW_COPY_AND_ASSIGN(FrameSwapMessageQueue);
};

}  

#endif  
