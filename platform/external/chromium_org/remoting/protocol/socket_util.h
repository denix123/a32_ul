// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_SOCKET_UTIL_H_
#define REMOTING_PROTOCOL_SOCKET_UTIL_H_

namespace remoting {

enum SocketErrorAction {
  SOCKET_ERROR_ACTION_FAIL,
  SOCKET_ERROR_ACTION_IGNORE,
  SOCKET_ERROR_ACTION_RETRY,
};

SocketErrorAction GetSocketErrorAction(int error);

}  

#endif  
