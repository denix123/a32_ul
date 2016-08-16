// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_SANDBOX_BPF_TEST_RUNNER_H_
#define SANDBOX_LINUX_SECCOMP_BPF_SANDBOX_BPF_TEST_RUNNER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/linux/seccomp-bpf/sandbox_bpf_policy.h"
#include "sandbox/linux/tests/sandbox_test_runner.h"

namespace sandbox {

class BPFTesterDelegate {
 public:
  BPFTesterDelegate() {}
  virtual ~BPFTesterDelegate() {}

  
  
  
  virtual scoped_ptr<SandboxBPFPolicy> GetSandboxBPFPolicy() = 0;
  
  virtual void RunTestFunction() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(BPFTesterDelegate);
};

class SandboxBPFTestRunner : public SandboxTestRunner {
 public:
  
  
  explicit SandboxBPFTestRunner(BPFTesterDelegate* bpf_tester_delegate);
  virtual ~SandboxBPFTestRunner();

  virtual void Run() OVERRIDE;

  virtual bool ShouldCheckForLeaks() const OVERRIDE;

 private:
  scoped_ptr<BPFTesterDelegate> bpf_tester_delegate_;
  DISALLOW_COPY_AND_ASSIGN(SandboxBPFTestRunner);
};

}  

#endif  
