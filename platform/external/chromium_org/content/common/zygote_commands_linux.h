// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_ZYGOTE_COMMANDS_LINUX_H_
#define CONTENT_COMMON_ZYGOTE_COMMANDS_LINUX_H_

#include "base/posix/global_descriptors.h"
#include "ipc/ipc_descriptors.h"

namespace content {

static const char kZygoteBootMessage[] = "ZYGOTE_BOOT";

static const char kZygoteHelloMessage[] = "ZYGOTE_OK";

static const char kZygoteChildPingMessage[] = "CHILD_PING";

const size_t kZygoteMaxMessageLength = 8192;

const int kZygoteSocketPairFd =
    kPrimaryIPCChannel + base::GlobalDescriptors::kBaseDescriptor;

enum {
  
  kZygoteCommandFork = 0,

  
  kZygoteCommandReap = 1,

  
  kZygoteCommandGetTerminationStatus = 2,

  
  kZygoteCommandGetSandboxStatus = 3,

  
  
  kZygoteCommandForkRealPID = 4
};

}  

#endif  
