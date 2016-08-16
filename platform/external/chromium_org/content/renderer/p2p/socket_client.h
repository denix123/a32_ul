// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_P2P_SOCKET_CLIENT_H_
#define CONTENT_RENDERER_P2P_SOCKET_CLIENT_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "content/common/p2p_socket_type.h"
#include "net/base/ip_endpoint.h"

namespace rtc {
struct PacketOptions;
};

namespace content {

class P2PSocketClientDelegate;

class P2PSocketClient : public base::RefCountedThreadSafe<P2PSocketClient> {
 public:
  
  
  
  
  static scoped_refptr<P2PSocketClient> Create(
      P2PSocketType type,
      const net::IPEndPoint& local_address,
      const net::IPEndPoint& remote_address,
      P2PSocketClientDelegate* delegate);

  P2PSocketClient() {}

  
  virtual void Send(const net::IPEndPoint& address,
                    const std::vector<char>& data) = 0;

  
  
  virtual void SendWithDscp(const net::IPEndPoint& address,
                            const std::vector<char>& data,
                            const rtc::PacketOptions& options) = 0;

  virtual void SetOption(P2PSocketOption option, int value) = 0;

  
  virtual void Close() = 0;

  virtual int GetSocketID() const = 0;
  virtual void SetDelegate(P2PSocketClientDelegate* delegate) = 0;

 protected:
  virtual ~P2PSocketClient() {}

 private:
  
  friend class base::RefCountedThreadSafe<P2PSocketClient>;
};
}  

#endif  
