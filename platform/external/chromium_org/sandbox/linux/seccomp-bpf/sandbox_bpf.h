// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_SANDBOX_BPF_H__
#define SANDBOX_LINUX_SECCOMP_BPF_SANDBOX_BPF_H__

#include <stdint.h>

#include <map>
#include <set>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "sandbox/linux/seccomp-bpf/errorcode.h"
#include "sandbox/linux/seccomp-bpf/trap.h"
#include "sandbox/sandbox_export.h"

struct sock_filter;

namespace sandbox {
class CodeGen;
class SandboxBPFPolicy;
class SandboxUnittestHelper;
struct Instruction;

class SANDBOX_EXPORT SandboxBPF {
 public:
  enum SandboxStatus {
    STATUS_UNKNOWN,      
    STATUS_UNSUPPORTED,  
    STATUS_UNAVAILABLE,  
    STATUS_AVAILABLE,    
    STATUS_ENABLED       
  };

  
  
  
  
  enum SandboxThreadState {
    PROCESS_INVALID,
    PROCESS_SINGLE_THREADED,  
    
    
    PROCESS_MULTI_THREADED,   
  };

  
  
  typedef std::vector<struct sock_filter> Program;

  
  
  
  
  
  
  
  
  
  
  SandboxBPF();
  ~SandboxBPF();

  
  
  
  static bool IsValidSyscallNumber(int sysnum);

  
  
  
  
  
  static SandboxStatus SupportsSeccompSandbox(int proc_fd);

  
  
  static SandboxStatus SupportsSeccompThreadFilterSynchronization();

  
  
  
  
  
  void set_proc_fd(int proc_fd);

  
  
  void SetSandboxPolicy(SandboxBPFPolicy* policy);

  
  
  
  
  
  
  static ErrorCode Trap(Trap::TrapFnc fnc, const void* aux);

  
  
  
  
  
  
  
  
  
  
  static ErrorCode UnsafeTrap(Trap::TrapFnc fnc, const void* aux);

  
  
  static bool IsRequiredForUnsafeTrap(int sysno);

  
  
  
  
  
  
  
  
  static intptr_t ForwardSyscall(const struct arch_seccomp_data& args);

  
  
  
  
  
  
  
  
  
  ErrorCode CondMaskedEqual(int argno,
                            ErrorCode::ArgType is_32bit,
                            uint64_t mask,
                            uint64_t value,
                            const ErrorCode& passed,
                            const ErrorCode& failed);

  
  
  ErrorCode Cond(int argno,
                 ErrorCode::ArgType is_32bit,
                 ErrorCode::Operation op,
                 uint64_t value,
                 const ErrorCode& passed,
                 const ErrorCode& failed);

  
  static ErrorCode Kill(const char* msg);

  
  
  
  
  
  
  
  
  
  
  
  
  
  bool StartSandbox(SandboxThreadState thread_state) WARN_UNUSED_RESULT;

  
  
  
  
  
  
  
  
  Program* AssembleFilter(bool force_verification);

  
  
  
  static ErrorCode Unexpected64bitArgument();

 private:
  friend class CodeGen;
  friend class SandboxUnittestHelper;
  friend class ErrorCode;

  struct Range {
    Range(uint32_t f, uint32_t t, const ErrorCode& e)
        : from(f), to(t), err(e) {}
    uint32_t from, to;
    ErrorCode err;
  };
  typedef std::vector<Range> Ranges;
  typedef std::map<uint32_t, ErrorCode> ErrMap;
  typedef std::set<ErrorCode, struct ErrorCode::LessThan> Conds;

  
  
  enum ArgHalf {
    LowerHalf,
    UpperHalf,
  };

  
  int proc_fd() { return proc_fd_; }

  
  
  
  bool RunFunctionInPolicy(void (*code_in_sandbox)(),
                           scoped_ptr<SandboxBPFPolicy> policy);

  
  
  
  
  bool KernelSupportSeccompBPF();

  
  void PolicySanityChecks(SandboxBPFPolicy* policy);

  
  
  void InstallFilter(bool must_sync_threads);

  
  
  Instruction* CompilePolicy(CodeGen* gen, bool* has_unsafe_traps);

  
  
  
  Instruction* CheckArch(CodeGen* gen, Instruction* passed);

  
  
  
  
  
  
  
  Instruction* MaybeAddEscapeHatch(CodeGen* gen,
                                   bool* has_unsafe_traps,
                                   Instruction* rest);

  
  
  
  
  Instruction* DispatchSyscall(CodeGen* gen);

  
  
  
  Instruction* CheckSyscallNumber(CodeGen* gen, Instruction* passed);

  
  
  
  void VerifyProgram(const Program& program, bool has_unsafe_traps);

  
  
  
  
  void FindRanges(Ranges* ranges);

  
  
  Instruction* AssembleJumpTable(CodeGen* gen,
                                 Ranges::const_iterator start,
                                 Ranges::const_iterator stop);

  
  
  
  
  
  Instruction* RetExpression(CodeGen* gen, const ErrorCode& err);

  
  
  
  
  Instruction* CondExpression(CodeGen* gen, const ErrorCode& cond);

  
  
  Instruction* CondExpressionHalf(CodeGen* gen,
                                  const ErrorCode& cond,
                                  ArgHalf half,
                                  Instruction* passed,
                                  Instruction* failed);

  static SandboxStatus status_;

  bool quiet_;
  int proc_fd_;
  scoped_ptr<const SandboxBPFPolicy> policy_;
  Conds* conds_;
  bool sandbox_has_started_;

  DISALLOW_COPY_AND_ASSIGN(SandboxBPF);
};

}  

#endif  
