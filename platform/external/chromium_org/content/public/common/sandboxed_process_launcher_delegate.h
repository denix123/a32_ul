// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_SANDBOXED_PROCESS_LAUNCHER_DELEGATE_H_
#define CONTENT_PUBLIC_COMMON_SANDBOXED_PROCESS_LAUNCHER_DELEGATE_H_

#include "base/environment.h"
#include "base/process/process.h"

#include "content/common/content_export.h"

#if defined(OS_MACOSX)
#include "content/public/common/sandbox_type_mac.h"
#endif

namespace base {
class FilePath;
}

namespace sandbox {
class TargetPolicy;
}

namespace content {

class CONTENT_EXPORT SandboxedProcessLauncherDelegate {
 public:
  virtual ~SandboxedProcessLauncherDelegate() {}

#if defined(OS_WIN)
  
  
  virtual bool ShouldLaunchElevated();

  
  
  
  virtual bool ShouldSandbox();

  
  
  
  
  virtual void PreSandbox(bool* disable_default_policy,
                          base::FilePath* exposed_dir) {}

  
  virtual void PreSpawnTarget(sandbox::TargetPolicy* policy,
                              bool* success) {}

  
  virtual void PostSpawnTarget(base::ProcessHandle process) {}

#elif defined(OS_POSIX)
  
  virtual bool ShouldUseZygote();

  
  virtual base::EnvironmentMap GetEnvironment();

  
  virtual int GetIpcFd() = 0;

#if defined(OS_MACOSX)
  
  
  virtual SandboxType GetSandboxType();
#endif

#endif
};

}  

#endif  
