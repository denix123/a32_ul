// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_CHILD_PROCESS_HOST_H_
#define MOJO_SHELL_CHILD_PROCESS_HOST_H_

#include "base/macros.h"
#include "base/process/process_handle.h"
#include "mojo/embedder/platform_channel_pair.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "mojo/shell/child_process.h"  

namespace mojo {
namespace shell {

class Context;

class ChildProcessHost {
 public:
  class Delegate {
   public:
    virtual void WillStart() = 0;
    virtual void DidStart(bool success) = 0;
  };

  ChildProcessHost(Context* context,
                   Delegate* delegate,
                   ChildProcess::Type type);
  virtual ~ChildProcessHost();

  
  
  
  
  
  void Start();

  
  
  
  int Join();

  embedder::ScopedPlatformHandle* platform_channel() {
    return &platform_channel_;
  }

 protected:
  Context* context() const {
    return context_;
  }

 private:
  bool DoLaunch();
  void DidLaunch(bool success);

  Context* const context_;
  Delegate* const delegate_;
  const ChildProcess::Type type_;

  base::ProcessHandle child_process_handle_;

  embedder::PlatformChannelPair platform_channel_pair_;

  
  
  embedder::ScopedPlatformHandle platform_channel_;

  DISALLOW_COPY_AND_ASSIGN(ChildProcessHost);
};

}  
}  

#endif  
