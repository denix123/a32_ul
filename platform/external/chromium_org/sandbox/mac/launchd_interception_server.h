// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_LAUNCHD_INTERCEPTION_SERVER_H_
#define SANDBOX_MAC_LAUNCHD_INTERCEPTION_SERVER_H_

#include <dispatch/dispatch.h>

#include "base/mac/scoped_mach_port.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/mac/message_server.h"
#include "sandbox/mac/os_compatibility.h"

namespace sandbox {

class BootstrapSandbox;
struct BootstrapSandboxPolicy;

class LaunchdInterceptionServer : public MessageDemuxer {
 public:
  explicit LaunchdInterceptionServer(const BootstrapSandbox* sandbox);
  virtual ~LaunchdInterceptionServer();

  
  
  
  bool Initialize(mach_port_t server_receive_right);

  
  virtual void DemuxMessage(IPCMessage request) OVERRIDE;

  mach_port_t server_port() const { return message_server_->GetServerPort(); }

 private:
  
  
  void HandleLookUp(IPCMessage request, const BootstrapSandboxPolicy* policy);

  
  
  
  void HandleSwapInteger(IPCMessage request);

  
  void ForwardMessage(IPCMessage request);

  
  const BootstrapSandbox* sandbox_;

  
  scoped_ptr<MessageServer> message_server_;

  
  
  base::mac::ScopedMachReceiveRight sandbox_port_;
  
  
  base::mac::ScopedMachSendRight sandbox_send_port_;

  
  
  const LaunchdCompatibilityShim compat_shim_;
};

}  

#endif  
