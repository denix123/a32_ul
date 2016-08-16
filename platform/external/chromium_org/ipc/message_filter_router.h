// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_MESSAGE_FILTER_ROUTER_H_
#define IPC_MESSAGE_FILTER_ROUTER_H_

#include <vector>

#include "ipc/ipc_message_start.h"

namespace IPC {

class Message;
class MessageFilter;

class MessageFilterRouter {
 public:
  typedef std::vector<MessageFilter*> MessageFilters;

  MessageFilterRouter();
  ~MessageFilterRouter();

  void AddFilter(MessageFilter* filter);
  void RemoveFilter(MessageFilter* filter);
  bool TryFilters(const Message& message);
  void Clear();

 private:
  
  
  
  
  
  
  MessageFilters global_filters_;
  MessageFilters message_class_filters_[LastIPCMsgStart];
};

}  

#endif  
