// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_SOCKET_DESCRIPTOR_H_
#define NET_SOCKET_SOCKET_DESCRIPTOR_H_

#include "build/build_config.h"
#include "net/base/net_export.h"

#if defined(OS_WIN)
#include <winsock2.h>
#endif  

namespace net {

#if defined(OS_POSIX)
typedef int SocketDescriptor;
const SocketDescriptor kInvalidSocket = -1;
#elif defined(OS_WIN)
typedef SOCKET SocketDescriptor;
const SocketDescriptor kInvalidSocket = INVALID_SOCKET;
#endif

class NET_EXPORT PlatformSocketFactory {
 public:
  PlatformSocketFactory();
  virtual ~PlatformSocketFactory();

  
  
  static void SetInstance(PlatformSocketFactory* factory);

  
  virtual SocketDescriptor CreateSocket(int family, int type, int protocol) = 0;
};

SocketDescriptor NET_EXPORT CreatePlatformSocket(int family,
                                                 int type,
                                                 int protocol);

}  

#endif  