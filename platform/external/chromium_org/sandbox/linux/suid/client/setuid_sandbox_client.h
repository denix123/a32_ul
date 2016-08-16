// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SUID_SETUID_SANDBOX_CLIENT_H_
#define SANDBOX_LINUX_SUID_SETUID_SANDBOX_CLIENT_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/files/scoped_file.h"
#include "base/process/launch.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class SANDBOX_EXPORT SetuidSandboxClient {
 public:
  
  static class SetuidSandboxClient* Create();
  ~SetuidSandboxClient();

  
  void CloseDummyFile();
  
  
  
  bool ChrootMe();
  
  
  
  
  bool CreateInitProcessReaper(base::Closure* post_fork_parent_callback);

  
  bool IsSuidSandboxUpToDate() const;
  
  bool IsSuidSandboxChild() const;
  
  bool IsInNewPIDNamespace() const;
  
  bool IsInNewNETNamespace() const;
  
  bool IsSandboxed() const;

  
  
  bool IsDisabledViaEnvironment();
  
  
  
  base::FilePath GetSandboxBinaryPath();
  
  
  void PrependWrapper(base::CommandLine* cmd_line);
  
  
  
  
  
  void SetupLaunchOptions(base::LaunchOptions* options,
                          base::FileHandleMappingVector* fds_to_remap,
                          base::ScopedFD* dummy_fd);
  
  
  void SetupLaunchEnvironment();

 private:
  SetuidSandboxClient();

  
  base::Environment* env_;
  bool sandboxed_;

  DISALLOW_COPY_AND_ASSIGN(SetuidSandboxClient);
};

}  

#endif  
