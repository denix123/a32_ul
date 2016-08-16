// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SANDBOX_LINUX_ANDROID_SANDBOX_BPF_BASE_POLICY_ANDROID_H_
#define CONTENT_COMMON_SANDBOX_LINUX_ANDROID_SANDBOX_BPF_BASE_POLICY_ANDROID_H_

#include "content/common/sandbox_linux/sandbox_bpf_base_policy_linux.h"

namespace content {

class SandboxBPFBasePolicyAndroid : public SandboxBPFBasePolicy {
 public:
  SandboxBPFBasePolicyAndroid();
  virtual ~SandboxBPFBasePolicyAndroid();

  
  virtual sandbox::bpf_dsl::ResultExpr EvaluateSyscall(
      int system_call_number) const OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(SandboxBPFBasePolicyAndroid);
};

}  

#endif  
