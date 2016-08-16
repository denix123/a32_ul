// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_HELPERS_SIGSYS_HANDLERS_H_
#define SANDBOX_LINUX_SECCOMP_BPF_HELPERS_SIGSYS_HANDLERS_H_

#include "base/basictypes.h"
#include "build/build_config.h"
#include "sandbox/linux/bpf_dsl/bpf_dsl.h"
#include "sandbox/sandbox_export.h"


namespace sandbox {

struct arch_seccomp_data;

SANDBOX_EXPORT intptr_t
    CrashSIGSYS_Handler(const struct arch_seccomp_data& args, void* aux);


SANDBOX_EXPORT intptr_t
    SIGSYSCloneFailure(const struct arch_seccomp_data& args, void* aux);
SANDBOX_EXPORT intptr_t
    SIGSYSPrctlFailure(const struct arch_seccomp_data& args, void* aux);
SANDBOX_EXPORT intptr_t
    SIGSYSIoctlFailure(const struct arch_seccomp_data& args, void* aux);
SANDBOX_EXPORT intptr_t
    SIGSYSKillFailure(const struct arch_seccomp_data& args, void* aux);
SANDBOX_EXPORT intptr_t
    SIGSYSFutexFailure(const struct arch_seccomp_data& args, void* aux);
SANDBOX_EXPORT intptr_t
    SIGSYSSchedHandler(const struct arch_seccomp_data& args, void* aux);

SANDBOX_EXPORT bpf_dsl::ResultExpr CrashSIGSYS();
SANDBOX_EXPORT bpf_dsl::ResultExpr CrashSIGSYSClone();
SANDBOX_EXPORT bpf_dsl::ResultExpr CrashSIGSYSPrctl();
SANDBOX_EXPORT bpf_dsl::ResultExpr CrashSIGSYSIoctl();
SANDBOX_EXPORT bpf_dsl::ResultExpr CrashSIGSYSKill();
SANDBOX_EXPORT bpf_dsl::ResultExpr CrashSIGSYSFutex();
SANDBOX_EXPORT bpf_dsl::ResultExpr RewriteSchedSIGSYS();

SANDBOX_EXPORT const char* GetErrorMessageContentForTests();
SANDBOX_EXPORT const char* GetCloneErrorMessageContentForTests();
SANDBOX_EXPORT const char* GetPrctlErrorMessageContentForTests();
SANDBOX_EXPORT const char* GetIoctlErrorMessageContentForTests();
SANDBOX_EXPORT const char* GetKillErrorMessageContentForTests();
SANDBOX_EXPORT const char* GetFutexErrorMessageContentForTests();

}  

#endif  
