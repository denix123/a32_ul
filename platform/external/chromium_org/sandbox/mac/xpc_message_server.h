// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_XPC_MESSAGE_SERVER_H_
#define SANDBOX_MAC_XPC_MESSAGE_SERVER_H_

#include "base/mac/scoped_mach_port.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/mac/message_server.h"
#include "sandbox/mac/xpc.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class DispatchSourceMach;

class SANDBOX_EXPORT XPCMessageServer : public MessageServer {
 public:
  
  
  
  
  XPCMessageServer(MessageDemuxer* demuxer,
                   mach_port_t server_receive_right);
  virtual ~XPCMessageServer();

  
  virtual bool Initialize() OVERRIDE;
  virtual pid_t GetMessageSenderPID(IPCMessage request) OVERRIDE;
  virtual IPCMessage CreateReply(IPCMessage request) OVERRIDE;
  virtual bool SendReply(IPCMessage reply) OVERRIDE;
  virtual void ForwardMessage(IPCMessage request,
                              mach_port_t destination) OVERRIDE;
  
  virtual void RejectMessage(IPCMessage request, int error_code) OVERRIDE;
  virtual mach_port_t GetServerPort() const OVERRIDE;

 private:
  
  void ReceiveMessage();

  
  MessageDemuxer* demuxer_;

  
  base::mac::ScopedMachReceiveRight server_port_;

  
  scoped_ptr<DispatchSourceMach> dispatch_source_;

  
  xpc_object_t reply_message_;

  DISALLOW_COPY_AND_ASSIGN(XPCMessageServer);
};

}  

#endif  
