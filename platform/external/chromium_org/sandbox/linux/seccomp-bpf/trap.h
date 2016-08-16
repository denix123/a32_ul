// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_TRAP_H__
#define SANDBOX_LINUX_SECCOMP_BPF_TRAP_H__

#include <signal.h>
#include <stdint.h>

#include <map>

#include "base/macros.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

struct arch_seccomp_data {
  int nr;
  uint32_t arch;
  uint64_t instruction_pointer;
  uint64_t args[6];
};

class SANDBOX_EXPORT Trap {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef intptr_t (*TrapFnc)(const struct arch_seccomp_data& args, void* aux);

  
  
  
  
  static uint16_t MakeTrap(TrapFnc fnc, const void* aux, bool safe);

  
  
  
  
  
  
  
  
  static bool EnableUnsafeTrapsInSigSysHandler();

  
  
  static bool IsSafeTrapId(uint16_t id);

 private:
  struct TrapKey {
    TrapKey() : fnc(NULL), aux(NULL), safe(false) {}
    TrapKey(TrapFnc f, const void* a, bool s) : fnc(f), aux(a), safe(s) {}
    TrapFnc fnc;
    const void* aux;
    bool safe;
    bool operator<(const TrapKey&) const;
  };
  typedef std::map<TrapKey, uint16_t> TrapIds;

  
  
  Trap();

  
  
  ~Trap();

  
  
  
  
  
  
  
  static Trap* GetInstance();
  static void SigSysAction(int nr, siginfo_t* info, void* void_context);

  
  
  void SigSys(int nr, siginfo_t* info, void* void_context)
      __attribute__((noinline));
  uint16_t MakeTrapImpl(TrapFnc fnc, const void* aux, bool safe);
  bool SandboxDebuggingAllowedByUser() const;

  
  
  
  
  static Trap* global_trap_;

  TrapIds trap_ids_;            
  TrapKey* trap_array_;         
  size_t trap_array_size_;      
  size_t trap_array_capacity_;  
  bool has_unsafe_traps_;       

  
  
  DISALLOW_COPY_AND_ASSIGN(Trap);
};

}  

#endif  
