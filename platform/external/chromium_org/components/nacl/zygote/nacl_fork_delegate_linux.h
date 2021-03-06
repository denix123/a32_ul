// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_ZYGOTE_NACL_FORK_DELEGATE_LINUX_H_
#define COMPONENTS_NACL_ZYGOTE_NACL_FORK_DELEGATE_LINUX_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "content/public/common/zygote_fork_delegate_linux.h"

namespace base {
struct LaunchOptions;
}

template <typename>
class ScopedVector;

namespace nacl {

void AddNaClZygoteForkDelegates(
    ScopedVector<content::ZygoteForkDelegate>* delegates);

class NaClForkDelegate : public content::ZygoteForkDelegate {
 public:
  explicit NaClForkDelegate(bool nonsfi_mode);
  virtual ~NaClForkDelegate();

  virtual void Init(int sandboxdesc, bool enable_layer1_sandbox) OVERRIDE;
  virtual void InitialUMA(std::string* uma_name,
                          int* uma_sample,
                          int* uma_boundary_value) OVERRIDE;
  virtual bool CanHelp(const std::string& process_type, std::string* uma_name,
                          int* uma_sample, int* uma_boundary_value) OVERRIDE;
  virtual pid_t Fork(const std::string& process_type,
                     const std::vector<int>& fds,
                     const std::string& channel_id) OVERRIDE;
  virtual bool GetTerminationStatus(pid_t pid, bool known_dead,
                                    base::TerminationStatus* status,
                                    int* exit_code) OVERRIDE;

 private:
  static void AddPassthroughEnvToOptions(base::LaunchOptions* options);

  
  
  enum NaClHelperStatus {
    kNaClHelperUnused = 0,
    kNaClHelperMissing = 1,
    kNaClHelperBootstrapMissing = 2,
    kNaClHelperValgrind = 3,
    kNaClHelperLaunchFailed = 4,
    kNaClHelperAckFailed = 5,
    kNaClHelperSuccess = 6,
    kNaClHelperStatusBoundary  
  };

  const bool nonsfi_mode_;
  NaClHelperStatus status_;
  int fd_;

  FRIEND_TEST_ALL_PREFIXES(NaClForkDelegateLinuxTest, EnvPassthrough);

  DISALLOW_COPY_AND_ASSIGN(NaClForkDelegate);
};

}  

#endif  
