// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_LOADER_NONSFI_NONSFI_SANDBOX_H_
#define COMPONENTS_NACL_LOADER_NONSFI_NONSFI_SANDBOX_H_

#include "base/basictypes.h"
#include "sandbox/linux/bpf_dsl/bpf_dsl.h"

namespace nacl {
namespace nonsfi {

class NaClNonSfiBPFSandboxPolicy
    : public sandbox::bpf_dsl::SandboxBPFDSLPolicy {
 public:
  explicit NaClNonSfiBPFSandboxPolicy() {}
  virtual ~NaClNonSfiBPFSandboxPolicy() {}

  virtual sandbox::bpf_dsl::ResultExpr EvaluateSyscall(
      int sysno) const OVERRIDE;
  virtual sandbox::bpf_dsl::ResultExpr InvalidSyscall() const OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NaClNonSfiBPFSandboxPolicy);
};

bool InitializeBPFSandbox();

}  
}  

#endif  
