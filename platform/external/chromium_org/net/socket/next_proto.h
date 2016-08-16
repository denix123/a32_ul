// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_NEXT_PROTO_H_
#define NET_SOCKET_NEXT_PROTO_H_

#include <vector>

#include "net/base/net_export.h"

namespace net {

enum NextProto {
  kProtoUnknown = 0,
  kProtoHTTP11 = 1,
  kProtoMinimumVersion = kProtoHTTP11,

  kProtoDeprecatedSPDY2 = 100,
  kProtoSPDYMinimumVersion = kProtoDeprecatedSPDY2,
  kProtoSPDY3 = 101,
  kProtoSPDY31 = 102,
  kProtoSPDY4 = 103,  
  kProtoSPDYMaximumVersion = kProtoSPDY4,

  kProtoQUIC1SPDY3 = 200,

  kProtoMaximumVersion = kProtoQUIC1SPDY3,
};

typedef std::vector<NextProto> NextProtoVector;


NET_EXPORT NextProtoVector NextProtosHttpOnly();

NET_EXPORT NextProtoVector NextProtosDefaults();

NET_EXPORT NextProtoVector NextProtosWithSpdyAndQuic(bool spdy_enabled,
                                                     bool quic_enabled);

NET_EXPORT NextProtoVector NextProtosSpdy3();
NET_EXPORT NextProtoVector NextProtosSpdy31();
NET_EXPORT NextProtoVector NextProtosSpdy31WithSpdy2();
NET_EXPORT NextProtoVector NextProtosSpdy4Http2();

}  

#endif  
