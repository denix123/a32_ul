// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SANDBOX_LINUX_BPF_GPU_POLICY_LINUX_H_
#define CONTENT_COMMON_SANDBOX_LINUX_BPF_GPU_POLICY_LINUX_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "content/common/sandbox_linux/sandbox_bpf_base_policy_linux.h"

namespace sandbox {
class BrokerProcess;
}

namespace content {

class GpuProcessPolicy : public SandboxBPFBasePolicy {
 public:
  GpuProcessPolicy();
  virtual ~GpuProcessPolicy();

  virtual sandbox::bpf_dsl::ResultExpr EvaluateSyscall(
      int system_call_number) const OVERRIDE;

  virtual bool PreSandboxHook() OVERRIDE;

 protected:
  
  
  
  
  
  
  void InitGpuBrokerProcess(
      sandbox::bpf_dsl::SandboxBPFDSLPolicy* (*broker_sandboxer_allocator)(
          void),
      const std::vector<std::string>& read_whitelist_extra,
      const std::vector<std::string>& write_whitelist_extra);

  sandbox::BrokerProcess* broker_process() { return broker_process_; }

 private:
  
  
  
  
  
  
  
  sandbox::BrokerProcess* broker_process_;
  DISALLOW_COPY_AND_ASSIGN(GpuProcessPolicy);
};

}  

#endif  
