// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_COMMON_P2P_SOCKET_TYPE_H_
#define CONTENT_COMMON_P2P_SOCKET_TYPE_H_

#include <string>

#include "net/base/ip_endpoint.h"

namespace content {

enum P2PSocketOption {
  P2P_SOCKET_OPT_RCVBUF,  
  P2P_SOCKET_OPT_SNDBUF,  
  P2P_SOCKET_OPT_DSCP,    
  P2P_SOCKET_OPT_MAX
};

enum P2PSocketType {
  P2P_SOCKET_UDP,
  P2P_SOCKET_TCP_SERVER,
  P2P_SOCKET_STUN_TCP_SERVER,
  P2P_SOCKET_TCP_CLIENT,
  P2P_SOCKET_STUN_TCP_CLIENT,
  P2P_SOCKET_SSLTCP_CLIENT,
  P2P_SOCKET_STUN_SSLTCP_CLIENT,
  P2P_SOCKET_TLS_CLIENT,
  P2P_SOCKET_STUN_TLS_CLIENT,
  P2P_SOCKET_TYPE_LAST = P2P_SOCKET_STUN_TLS_CLIENT
};

struct P2PHostAndIPEndPoint {
  P2PHostAndIPEndPoint() {}
  P2PHostAndIPEndPoint(const std::string& hostname,
                       const net::IPEndPoint& ip_address)
      : hostname(hostname), ip_address(ip_address) {
  }

  std::string hostname;
  net::IPEndPoint ip_address;
};

}  

#endif  
