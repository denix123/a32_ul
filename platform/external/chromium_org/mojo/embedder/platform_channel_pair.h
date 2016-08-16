// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_PLATFORM_CHANNEL_PAIR_H_
#define MOJO_EMBEDDER_PLATFORM_CHANNEL_PAIR_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/launch.h"
#include "build/build_config.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "mojo/system/system_impl_export.h"

namespace base {
class CommandLine;
}

namespace mojo {
namespace embedder {

#if defined(OS_WIN)
typedef base::HandlesToInheritVector HandlePassingInformation;
#elif defined(OS_POSIX)
typedef base::FileHandleMappingVector HandlePassingInformation;
#else
#error "Unsupported."
#endif

class MOJO_SYSTEM_IMPL_EXPORT PlatformChannelPair {
 public:
  PlatformChannelPair();
  ~PlatformChannelPair();

  ScopedPlatformHandle PassServerHandle();

  
  ScopedPlatformHandle PassClientHandle();

  
  
  
  
  static ScopedPlatformHandle PassClientHandleFromParentProcess(
      const base::CommandLine& command_line);

  
  
  
  
  void PrepareToPassClientHandleToChildProcess(
      base::CommandLine* command_line,
      HandlePassingInformation* handle_passing_info) const;

  
  
  void ChildProcessLaunched();

 private:
  static const char kMojoPlatformChannelHandleSwitch[];

  ScopedPlatformHandle server_handle_;
  ScopedPlatformHandle client_handle_;

  DISALLOW_COPY_AND_ASSIGN(PlatformChannelPair);
};

}  
}  

#endif  
