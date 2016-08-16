// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_HOST_EXTENSION_H_
#define REMOTING_HOST_HOST_EXTENSION_H_

#include <string>

#include "base/memory/scoped_ptr.h"

namespace remoting {

class ClientSessionControl;
class HostExtensionSession;

namespace protocol {
class ClientStub;
}

class HostExtension {
 public:
  virtual ~HostExtension() {}

  
  
  
  
  
  virtual std::string capability() const = 0;

  
  
  
  
  
  virtual scoped_ptr<HostExtensionSession> CreateExtensionSession(
      ClientSessionControl* client_session_control,
      protocol::ClientStub* client_stub) = 0;
};

}  

#endif  
