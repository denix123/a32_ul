// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_HELPERS_BASELINE_POLICY_H_
#define SANDBOX_LINUX_SECCOMP_BPF_HELPERS_BASELINE_POLICY_H_

#include "sandbox/linux/bpf_dsl/bpf_dsl.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class SANDBOX_EXPORT BaselinePolicy : public bpf_dsl::SandboxBPFDSLPolicy {
 public:
  BaselinePolicy();
  
  
  explicit BaselinePolicy(int fs_denied_errno);
  virtual ~BaselinePolicy();

  virtual bpf_dsl::ResultExpr EvaluateSyscall(
      int system_call_number) const OVERRIDE;
  virtual bpf_dsl::ResultExpr InvalidSyscall() const OVERRIDE;

 private:
  int fs_denied_errno_;
  pid_t current_pid_;
  DISALLOW_COPY_AND_ASSIGN(BaselinePolicy);
};

}  

#endif  
