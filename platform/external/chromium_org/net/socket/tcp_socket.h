// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_TCP_SOCKET_H_
#define NET_SOCKET_TCP_SOCKET_H_

#include "build/build_config.h"
#include "net/base/net_export.h"

#if defined(OS_WIN)
#include "net/socket/tcp_socket_win.h"
#elif defined(OS_POSIX)
#include "net/socket/tcp_socket_libevent.h"
#endif

namespace net {

#if defined(OS_WIN)
typedef TCPSocketWin TCPSocket;
#elif defined(OS_POSIX)
typedef TCPSocketLibevent TCPSocket;
#endif

bool IsTCPFastOpenSupported();

bool IsTCPFastOpenUserEnabled();

NET_EXPORT void CheckSupportAndMaybeEnableTCPFastOpen(bool user_enabled);

}  

#endif  
