// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_BPF_TESTER_COMPATIBILITY_DELEGATE_H_
#define SANDBOX_LINUX_SECCOMP_BPF_BPF_TESTER_COMPATIBILITY_DELEGATE_H_

#include "base/memory/scoped_ptr.h"
#include "sandbox/linux/seccomp-bpf/sandbox_bpf_test_runner.h"

namespace sandbox {

template <class Policy, class Aux>
class BPFTesterCompatibilityDelegate : public BPFTesterDelegate {
 public:
  typedef void (*TestFunction)(Aux*);

  explicit BPFTesterCompatibilityDelegate(TestFunction test_function)
      : aux_(), test_function_(test_function) {}

  virtual ~BPFTesterCompatibilityDelegate() {}

  virtual scoped_ptr<SandboxBPFPolicy> GetSandboxBPFPolicy() OVERRIDE {
    
    
    
    
    return scoped_ptr<SandboxBPFPolicy>(new Policy(&aux_));
  }

  virtual void RunTestFunction() OVERRIDE {
    
    
    
    test_function_(&aux_);
  }

 private:
  Aux aux_;
  TestFunction test_function_;

  DISALLOW_COPY_AND_ASSIGN(BPFTesterCompatibilityDelegate);
};

}  

#endif  
