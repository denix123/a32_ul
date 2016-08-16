// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_MESSAGE_FILTER_H_
#define IPC_MESSAGE_FILTER_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "ipc/ipc_export.h"

namespace IPC {

class Sender;
class Message;

class IPC_EXPORT MessageFilter
    : public base::RefCountedThreadSafe<MessageFilter> {
 public:
  MessageFilter();

  
  
  
  virtual void OnFilterAdded(Sender* sender);

  
  
  
  virtual void OnFilterRemoved();

  
  
  virtual void OnChannelConnected(int32 peer_pid);

  
  
  virtual void OnChannelError();

  
  
  virtual void OnChannelClosing();

  
  
  virtual bool OnMessageReceived(const Message& message);

  
  
  
  
  virtual bool GetSupportedMessageClasses(
      std::vector<uint32>* supported_message_classes) const;

 protected:
  virtual ~MessageFilter();

 private:
  friend class base::RefCountedThreadSafe<MessageFilter>;
};

}  

#endif  
