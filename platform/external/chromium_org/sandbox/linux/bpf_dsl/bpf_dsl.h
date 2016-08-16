// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_BPF_DSL_BPF_DSL_H_
#define SANDBOX_LINUX_BPF_DSL_BPF_DSL_H_

#include <stdint.h>

#include <utility>
#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "sandbox/linux/bpf_dsl/cons.h"
#include "sandbox/linux/seccomp-bpf/sandbox_bpf_policy.h"
#include "sandbox/linux/seccomp-bpf/trap.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {
class ErrorCode;
class SandboxBPF;
}


namespace sandbox {
namespace bpf_dsl {

class Elser;
template <typename T>
class Caser;
namespace internal {
class ResultExprImpl;
class BoolExprImpl;
}

typedef scoped_refptr<const internal::ResultExprImpl> ResultExpr;

typedef scoped_refptr<const internal::BoolExprImpl> BoolExpr;

class SANDBOX_EXPORT SandboxBPFDSLPolicy : public SandboxBPFPolicy {
 public:
  SandboxBPFDSLPolicy() : SandboxBPFPolicy() {}
  virtual ~SandboxBPFDSLPolicy() {}

  
  virtual ResultExpr EvaluateSyscall(int sysno) const = 0;

  
  
  virtual ResultExpr InvalidSyscall() const;

  
  
  
  virtual ErrorCode EvaluateSyscall(SandboxBPF* sb,
                                    int sysno) const OVERRIDE FINAL;
  virtual ErrorCode InvalidSyscall(SandboxBPF* sb) const OVERRIDE FINAL;

  
  static ResultExpr Trap(Trap::TrapFnc trap_func, const void* aux);

 private:
  DISALLOW_COPY_AND_ASSIGN(SandboxBPFDSLPolicy);
};

SANDBOX_EXPORT ResultExpr Allow();

SANDBOX_EXPORT ResultExpr Error(int err);

SANDBOX_EXPORT ResultExpr Kill(const char* msg);

SANDBOX_EXPORT ResultExpr Trace(uint16_t aux);

SANDBOX_EXPORT ResultExpr Trap(Trap::TrapFnc trap_func, const void* aux);

SANDBOX_EXPORT ResultExpr UnsafeTrap(Trap::TrapFnc trap_func, const void* aux);

SANDBOX_EXPORT BoolExpr BoolConst(bool value);

SANDBOX_EXPORT BoolExpr operator!(const BoolExpr& cond);
SANDBOX_EXPORT BoolExpr operator&&(const BoolExpr& lhs, const BoolExpr& rhs);
SANDBOX_EXPORT BoolExpr operator||(const BoolExpr& lhs, const BoolExpr& rhs);

template <typename T>
class SANDBOX_EXPORT Arg {
 public:
  
  
  explicit Arg(int num);

  Arg(const Arg& arg) : num_(arg.num_), mask_(arg.mask_) {}

  
  
  friend Arg operator&(const Arg& lhs, uint64_t rhs) {
    return Arg(lhs.num_, lhs.mask_ & rhs);
  }

  
  
  friend BoolExpr operator==(const Arg& lhs, T rhs) { return lhs.EqualTo(rhs); }

  
  
  friend BoolExpr operator!=(const Arg& lhs, T rhs) { return !(lhs == rhs); }

 private:
  Arg(int num, uint64_t mask) : num_(num), mask_(mask) {}

  BoolExpr EqualTo(T val) const;

  int num_;
  uint64_t mask_;

  DISALLOW_ASSIGN(Arg);
};

SANDBOX_EXPORT Elser If(const BoolExpr& cond, const ResultExpr& then_result);

class SANDBOX_EXPORT Elser {
 public:
  Elser(const Elser& elser);
  ~Elser();

  
  
  Elser ElseIf(const BoolExpr& cond, const ResultExpr& then_result) const;

  
  
  ResultExpr Else(const ResultExpr& else_result) const;

 private:
  typedef std::pair<BoolExpr, ResultExpr> Clause;

  explicit Elser(Cons<Clause>::List clause_list);

  Cons<Clause>::List clause_list_;

  friend Elser If(const BoolExpr&, const ResultExpr&);
  template <typename T>
  friend Caser<T> Switch(const Arg<T>&);
  DISALLOW_ASSIGN(Elser);
};

template <typename T>
SANDBOX_EXPORT Caser<T> Switch(const Arg<T>& arg);

template <typename T>
class SANDBOX_EXPORT Caser {
 public:
  Caser(const Caser<T>& caser) : arg_(caser.arg_), elser_(caser.elser_) {}
  ~Caser() {}

  
  Caser<T> Case(T value, ResultExpr result) const;

  
  
  
  Caser<T> Cases(const std::vector<T>& values, ResultExpr result) const;

  
  ResultExpr Default(ResultExpr result) const;

 private:
  Caser(const Arg<T>& arg, Elser elser) : arg_(arg), elser_(elser) {}

  Arg<T> arg_;
  Elser elser_;

  template <typename U>
  friend Caser<U> Switch(const Arg<U>&);
  DISALLOW_ASSIGN(Caser);
};

#define SANDBOX_BPF_DSL_CASES(values, result) \
  Cases(SANDBOX_BPF_DSL_CASES_HELPER values, result)

#define SANDBOX_BPF_DSL_CASES_HELPER(value, ...)                           \
  ({                                                                       \
    const __typeof__(value) bpf_dsl_cases_values[] = {value, __VA_ARGS__}; \
    std::vector<__typeof__(value)>(                                        \
        bpf_dsl_cases_values,                                              \
        bpf_dsl_cases_values + arraysize(bpf_dsl_cases_values));           \
  })


namespace internal {

using bpf_dsl::operator!;
using bpf_dsl::operator||;
using bpf_dsl::operator&&;

SANDBOX_EXPORT BoolExpr
    ArgEq(int num, size_t size, uint64_t mask, uint64_t val);

SANDBOX_EXPORT uint64_t DefaultMask(size_t size);

class SANDBOX_EXPORT BoolExprImpl : public base::RefCounted<BoolExprImpl> {
 public:
  BoolExprImpl() {}
  virtual ErrorCode Compile(SandboxBPF* sb,
                            ErrorCode true_ec,
                            ErrorCode false_ec) const = 0;

 protected:
  virtual ~BoolExprImpl() {}

 private:
  friend class base::RefCounted<BoolExprImpl>;
  DISALLOW_COPY_AND_ASSIGN(BoolExprImpl);
};

class SANDBOX_EXPORT ResultExprImpl : public base::RefCounted<ResultExprImpl> {
 public:
  ResultExprImpl() {}
  virtual ErrorCode Compile(SandboxBPF* sb) const = 0;

 protected:
  virtual ~ResultExprImpl() {}

 private:
  friend class base::RefCounted<ResultExprImpl>;
  DISALLOW_COPY_AND_ASSIGN(ResultExprImpl);
};

}  

template <typename T>
Arg<T>::Arg(int num)
    : num_(num), mask_(internal::DefaultMask(sizeof(T))) {
}

template <typename T>
BoolExpr Arg<T>::EqualTo(T val) const {
  return internal::ArgEq(num_, sizeof(T), mask_, static_cast<uint64_t>(val));
}

template <typename T>
SANDBOX_EXPORT Caser<T> Switch(const Arg<T>& arg) {
  return Caser<T>(arg, Elser(Cons<Elser::Clause>::List()));
}

template <typename T>
Caser<T> Caser<T>::Case(T value, ResultExpr result) const {
  return SANDBOX_BPF_DSL_CASES((value), result);
}

template <typename T>
Caser<T> Caser<T>::Cases(const std::vector<T>& values,
                         ResultExpr result) const {
  
  
  

  typedef typename std::vector<T>::const_iterator Iter;
  BoolExpr test = BoolConst(false);
  for (Iter i = values.begin(), end = values.end(); i != end; ++i) {
    test = test || (arg_ == *i);
  }
  return Caser<T>(arg_, elser_.ElseIf(test, result));
}

template <typename T>
ResultExpr Caser<T>::Default(ResultExpr result) const {
  return elser_.Else(result);
}

}  
}  

#endif  
