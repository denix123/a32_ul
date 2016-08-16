// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_HELPERS_SYSCALL_PARAMETERS_RESTRICTIONS_H_
#define SANDBOX_LINUX_SECCOMP_BPF_HELPERS_SYSCALL_PARAMETERS_RESTRICTIONS_H_

#include <unistd.h>

#include "build/build_config.h"
#include "sandbox/linux/bpf_dsl/bpf_dsl.h"
#include "sandbox/sandbox_export.h"


namespace sandbox {

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictCloneToThreadsAndEPERMFork();

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictPrctl();

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictIoctl();

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictMmapFlags();

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictMprotectFlags();

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictFcntlCommands();

#if defined(__i386__) || defined(__mips__)
SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictSocketcallCommand();
#endif

bpf_dsl::ResultExpr RestrictKillTarget(pid_t target_pid, int sysno);

bpf_dsl::ResultExpr RestrictFutex();

bpf_dsl::ResultExpr RestrictGetSetpriority(pid_t target_pid);

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictClockID();

SANDBOX_EXPORT bpf_dsl::ResultExpr RestrictSchedTarget(pid_t target_pid,
                                                       int sysno);

}  

#endif  
