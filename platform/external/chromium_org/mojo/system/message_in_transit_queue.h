// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MESSAGE_QUEUE_H_
#define MOJO_SYSTEM_MESSAGE_QUEUE_H_

#include <deque>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/system/message_in_transit.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class MOJO_SYSTEM_IMPL_EXPORT MessageInTransitQueue {
 public:
  MessageInTransitQueue();
  ~MessageInTransitQueue();

  bool IsEmpty() const { return queue_.empty(); }

  void AddMessage(scoped_ptr<MessageInTransit> message) {
    queue_.push_back(message.release());
  }

  scoped_ptr<MessageInTransit> GetMessage() {
    MessageInTransit* rv = queue_.front();
    queue_.pop_front();
    return make_scoped_ptr(rv);
  }

  MessageInTransit* PeekMessage() { return queue_.front(); }

  void DiscardMessage() {
    delete queue_.front();
    queue_.pop_front();
  }

  void Clear();

  
  void Swap(MessageInTransitQueue* other);

 private:
  
  
  std::deque<MessageInTransit*> queue_;

  DISALLOW_COPY_AND_ASSIGN(MessageInTransitQueue);
};

}  
}  

#endif  
