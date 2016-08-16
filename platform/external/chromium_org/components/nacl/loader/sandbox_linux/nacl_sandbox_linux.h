// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_LOADER_SANDBOX_LINUX_NACL_SANDBOX_LINUX_H_
#define COMPONENTS_NACL_LOADER_SANDBOX_LINUX_NACL_SANDBOX_LINUX_H_

#include "base/files/scoped_file.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace sandbox {
class SetuidSandboxClient;
}

namespace nacl {

class NaClSandbox {
 public:
  NaClSandbox();
  ~NaClSandbox();

  
  
  bool IsSingleThreaded();
  
  
  
  
  
  bool HasOpenDirectory();
  
  
  
  void InitializeLayerOneSandbox();
  
  
  
  void InitializeLayerTwoSandbox(bool uses_nonsfi_mode);
  
  void SealLayerOneSandbox();
  
  
  void CheckSandboxingStateWithPolicy();

  bool layer_one_enabled() { return layer_one_enabled_; }
  bool layer_two_enabled() { return layer_two_enabled_; }

 private:
  void CheckForExpectedNumberOfOpenFds();

  bool layer_one_enabled_;
  bool layer_one_sealed_;
  bool layer_two_enabled_;
  bool layer_two_is_nonsfi_;
  
  
  base::ScopedFD proc_fd_;
  scoped_ptr<sandbox::SetuidSandboxClient> setuid_sandbox_client_;
  DISALLOW_COPY_AND_ASSIGN(NaClSandbox);
};

}  

#endif  
