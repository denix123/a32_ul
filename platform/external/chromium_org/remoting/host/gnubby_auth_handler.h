// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_GNUBBY_AUTH_HANDLER_H_
#define REMOTING_HOST_GNUBBY_AUTH_HANDLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class FilePath;
}  

namespace remoting {

namespace protocol {
class ClientStub;
}  

class GnubbyAuthHandler {
 public:
  virtual ~GnubbyAuthHandler() {}

  
  static scoped_ptr<GnubbyAuthHandler> Create(
      protocol::ClientStub* client_stub);

  
  static void SetGnubbySocketName(const base::FilePath& gnubby_socket_name);

  
  virtual void DeliverClientMessage(const std::string& message) = 0;

  
  virtual void DeliverHostDataMessage(int connection_id,
                                      const std::string& data) const = 0;
};

}  

#endif  
