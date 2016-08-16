// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SWAPPED_OUT_MESSAGES_H_
#define CONTENT_COMMON_SWAPPED_OUT_MESSAGES_H_

#include "ipc/ipc_message.h"

namespace content {

class SwappedOutMessages {
 public:
  static bool CanSendWhileSwappedOut(const IPC::Message* msg);
  static bool CanHandleWhileSwappedOut(const IPC::Message& msg);
};

}  

#endif  