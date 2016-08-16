// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SERVICES_SCOPED_PROCESS_H_
#define SANDBOX_LINUX_SERVICES_SCOPED_PROCESS_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/process/process_handle.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class SANDBOX_EXPORT ScopedProcess {
 public:
  
  
  
  explicit ScopedProcess(const base::Closure& child_callback);
  ~ScopedProcess();

  
  
  
  
  
  
  int WaitForExit(bool* got_signaled);

  
  
  
  bool WaitForClosureToRun();
  base::ProcessId GetPid() { return child_process_id_; }

 private:
  bool IsOriginalProcess();

  base::ProcessId child_process_id_;
  base::ProcessId process_id_;
  int pipe_fds_[2];
  DISALLOW_COPY_AND_ASSIGN(ScopedProcess);
};

}  

#endif  
