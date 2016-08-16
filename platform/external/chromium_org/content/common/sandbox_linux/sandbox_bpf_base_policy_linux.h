// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SANDBOX_LINUX_SANDBOX_BPF_BASE_POLICY_LINUX_H_
#define CONTENT_COMMON_SANDBOX_LINUX_SANDBOX_BPF_BASE_POLICY_LINUX_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/linux/bpf_dsl/bpf_dsl.h"
#include "sandbox/linux/seccomp-bpf-helpers/baseline_policy.h"

namespace content {

class SandboxBPFBasePolicy : public sandbox::bpf_dsl::SandboxBPFDSLPolicy {
 public:
  SandboxBPFBasePolicy();
  virtual ~SandboxBPFBasePolicy();

  virtual sandbox::bpf_dsl::ResultExpr EvaluateSyscall(
      int system_call_number) const OVERRIDE;
  virtual sandbox::bpf_dsl::ResultExpr InvalidSyscall() const OVERRIDE;

  
  
  
  
  
  
  virtual bool PreSandboxHook();

  
  static int GetFSDeniedErrno();

 private:
  
  scoped_ptr<sandbox::BaselinePolicy> baseline_policy_;
  DISALLOW_COPY_AND_ASSIGN(SandboxBPFBasePolicy);
};

}  

#endif  
