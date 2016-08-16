// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_MESSAGE_HANDLER_H_
#define PPAPI_CPP_MESSAGE_HANDLER_H_

namespace pp {

class MessageHandler {
 public:
  virtual ~MessageHandler() {};

  
  
  
  
  
  
  
  virtual void HandleMessage(pp::InstanceHandle instance,
                             const Var& message_data) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual pp::Var HandleBlockingMessage(pp::InstanceHandle instance,
                                        const Var& message_data) = 0;

  
  
  
  
  
  virtual void WasUnregistered(pp::InstanceHandle instance) = 0;
};

}  

#endif  
