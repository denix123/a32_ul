// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_MACH_MESSAGE_SERVER_H_
#define SANDBOX_MAC_MACH_MESSAGE_SERVER_H_

#include <mach/mach.h>

#include "base/mac/scoped_mach_port.h"
#include "base/mac/scoped_mach_vm.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/mac/message_server.h"

namespace sandbox {

class DispatchSourceMach;

class MachMessageServer : public MessageServer {
 public:
  
  
  
  
  
  MachMessageServer(MessageDemuxer* demuxer,
                    mach_port_t server_receive_right,
                    mach_msg_size_t buffer_size);
  virtual ~MachMessageServer();

  
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

  
  const mach_msg_size_t buffer_size_;

  
  base::mac::ScopedMachVM request_buffer_;
  base::mac::ScopedMachVM reply_buffer_;

  
  scoped_ptr<DispatchSourceMach> dispatch_source_;

  
  bool did_forward_message_;
};

}  

#endif  
