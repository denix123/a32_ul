// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef SANDBOX_MAC_OS_COMPATIBILITY_H_
#define SANDBOX_MAC_OS_COMPATIBILITY_H_

#include <mach/mach.h>

#include <string>

#include "sandbox/mac/message_server.h"

namespace sandbox {

typedef uint64_t (*IPCMessageGetID)(const IPCMessage);

typedef std::string (*LookUp2GetRequestName)(const IPCMessage);
typedef void (*LookUp2FillReply)(IPCMessage, mach_port_t service_port);

typedef bool (*SwapIntegerIsGetOnly)(const IPCMessage);

struct LaunchdCompatibilityShim {
  
  IPCMessageGetID ipc_message_get_id;

  
  uint64_t msg_id_look_up2;

  
  uint64_t msg_id_swap_integer;

  
  
  LookUp2GetRequestName look_up2_get_request_name;

  
  
  LookUp2FillReply look_up2_fill_reply;

  
  
  
  SwapIntegerIsGetOnly swap_integer_is_get_only;
};

const LaunchdCompatibilityShim GetLaunchdCompatibilityShim();

}  

#endif  
