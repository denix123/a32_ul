// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_MESSAGING_NATIVE_MESSAGING_CHANNEL_H_
#define EXTENSIONS_BROWSER_API_MESSAGING_NATIVE_MESSAGING_CHANNEL_H_

#include "base/callback.h"

namespace base {
class Value;
}  

namespace extensions {

class NativeMessagingChannel {
 public:
  
  
  class EventHandler {
   public:
    
    virtual void OnMessage(scoped_ptr<base::Value> message) = 0;

    
    
    virtual void OnDisconnect() = 0;

    virtual ~EventHandler() {}
  };

  virtual ~NativeMessagingChannel() {}

  
  virtual void Start(EventHandler* event_handler) = 0;

  
  virtual void SendMessage(scoped_ptr<base::Value> message) = 0;
};

}  

#endif  
