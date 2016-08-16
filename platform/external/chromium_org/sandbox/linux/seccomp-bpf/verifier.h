// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_VERIFIER_H__
#define SANDBOX_LINUX_SECCOMP_BPF_VERIFIER_H__

#include <stdint.h>

#include <vector>

#include "base/macros.h"

struct sock_filter;

namespace sandbox {
struct arch_seccomp_data;
class SandboxBPF;
class SandboxBPFPolicy;

class Verifier {
 public:
  
  
  
  
  
  
  
  static bool VerifyBPF(SandboxBPF* sandbox,
                        const std::vector<struct sock_filter>& program,
                        const SandboxBPFPolicy& policy,
                        const char** err);

  
  
  
  
  
  
  
  
  static uint32_t EvaluateBPF(const std::vector<struct sock_filter>& program,
                              const struct arch_seccomp_data& data,
                              const char** err);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Verifier);
};

}  

#endif  
