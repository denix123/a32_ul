// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SANDBOX_LINUX_SANDBOX_LINUX_H_
#define CONTENT_COMMON_SANDBOX_LINUX_SANDBOX_LINUX_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/common/sandbox_linux.h"

#if defined(ADDRESS_SANITIZER) || defined(MEMORY_SANITIZER) || \
    defined(LEAK_SANITIZER) || defined(UNDEFINED_SANITIZER)
#include <sanitizer/common_interface_defs.h>
#endif

template <typename T> struct DefaultSingletonTraits;
namespace base {
class Thread;
}
namespace sandbox { class SetuidSandboxClient; }

namespace content {

class LinuxSandbox {
 public:
  
  
  
  
  enum LinuxSandboxIPCMethods {
    METHOD_GET_FALLBACK_FONT_FOR_CHAR = 32,
    METHOD_LOCALTIME = 33,
    DEPRECATED_METHOD_GET_CHILD_WITH_INODE = 34,
    METHOD_GET_STYLE_FOR_STRIKE = 35,
    METHOD_MAKE_SHARED_MEMORY_SEGMENT = 36,
    METHOD_MATCH_WITH_FALLBACK = 37,
  };

  
  static LinuxSandbox* GetInstance();

  
  
  
  void PreinitializeSandbox();

  
  
  
  
  
  static bool InitializeSandbox();

  
  static void StopThread(base::Thread* thread);

  
  
  
  
  
  
  int GetStatus();
  
  
  bool IsSingleThreaded() const;
  
  bool seccomp_bpf_started() const;

  
  
  
  
  sandbox::SetuidSandboxClient* setuid_sandbox_client() const;

  
  
  
  bool StartSeccompBPF(const std::string& process_type);

  
  
  bool LimitAddressSpace(const std::string& process_type);

#if defined(ADDRESS_SANITIZER) || defined(MEMORY_SANITIZER) || \
    defined(LEAK_SANITIZER) || defined(UNDEFINED_SANITIZER)
  __sanitizer_sandbox_arguments* sanitizer_args() const {
    return sanitizer_args_.get();
  };
#endif

 private:
  friend struct DefaultSingletonTraits<LinuxSandbox>;

  LinuxSandbox();
  ~LinuxSandbox();

  
  
  bool InitializeSandboxImpl();
  void StopThreadImpl(base::Thread* thread);
  
  bool seccomp_bpf_supported() const;
  
  
  
  bool HasOpenDirectories() const;
  
  
  void SealSandbox();
  
  
  void CheckForBrokenPromises(const std::string& process_type);
  
  
  void StopThreadAndEnsureNotCounted(base::Thread* thread) const;

  
  
  
  int proc_fd_;
  bool seccomp_bpf_started_;
  
  int sandbox_status_flags_;
  
  bool pre_initialized_;
  bool seccomp_bpf_supported_;  
  bool yama_is_enforcing_;  
  scoped_ptr<sandbox::SetuidSandboxClient> setuid_sandbox_client_;
#if defined(ADDRESS_SANITIZER) || defined(MEMORY_SANITIZER) || \
    defined(LEAK_SANITIZER) || defined(UNDEFINED_SANITIZER)
  scoped_ptr<__sanitizer_sandbox_arguments> sanitizer_args_;
#endif

  DISALLOW_COPY_AND_ASSIGN(LinuxSandbox);
};

}  

#endif  
