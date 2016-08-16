// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_BOOTSTRAP_SANDBOX_H_
#define SANDBOX_MAC_BOOTSTRAP_SANDBOX_H_

#include <mach/mach.h>

#include <map>
#include <string>

#include "base/mac/scoped_mach_port.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/process_handle.h"
#include "base/synchronization/lock.h"
#include "sandbox/mac/policy.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class LaunchdInterceptionServer;

class SANDBOX_EXPORT BootstrapSandbox {
 public:
  
  static scoped_ptr<BootstrapSandbox> Create();

  ~BootstrapSandbox();

  
  
  void RegisterSandboxPolicy(int sandbox_policy_id,
                             const BootstrapSandboxPolicy& policy);

  
  
  
  void PrepareToForkWithPolicy(int sandbox_policy_id);

  
  
  
  void FinishedFork(base::ProcessHandle handle);

  
  
  void ChildDied(base::ProcessHandle handle);

  
  
  const BootstrapSandboxPolicy* PolicyForProcess(pid_t pid) const;

  std::string server_bootstrap_name() const { return server_bootstrap_name_; }
  mach_port_t real_bootstrap_port() const { return real_bootstrap_port_; }

 private:
  BootstrapSandbox();

  
  
  const std::string server_bootstrap_name_;

  
  
  base::mac::ScopedMachSendRight real_bootstrap_port_;

  
  mutable base::Lock lock_;

  
  int effective_policy_id_;

  
  std::map<int, const BootstrapSandboxPolicy> policies_;

  
  std::map<base::ProcessHandle, int> sandboxed_processes_;

  
  
  scoped_ptr<LaunchdInterceptionServer> server_;
};

}  

#endif  
