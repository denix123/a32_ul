// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_MESSAGE_SERVER_H_
#define SANDBOX_MAC_MESSAGE_SERVER_H_

#include <mach/mach.h>
#include <unistd.h>

#include "sandbox/mac/xpc.h"

namespace sandbox {

union IPCMessage {
  mach_msg_header_t* mach;
  xpc_object_t xpc;
};

class MessageDemuxer {
 public:
  
  
  virtual void DemuxMessage(IPCMessage request) = 0;

 protected:
  virtual ~MessageDemuxer() {}
};

class MessageServer {
 public:
  virtual ~MessageServer() {}

  
  
  virtual bool Initialize() = 0;

  
  virtual pid_t GetMessageSenderPID(IPCMessage request) = 0;

  
  
  virtual IPCMessage CreateReply(IPCMessage request) = 0;

  
  virtual bool SendReply(IPCMessage reply) = 0;

  
  virtual void ForwardMessage(IPCMessage request, mach_port_t destination) = 0;

  
  
  
  virtual void RejectMessage(IPCMessage request, int error_code) = 0;

  
  virtual mach_port_t GetServerPort() const = 0;
};

}  

#endif  
