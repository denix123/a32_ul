// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_ARGS_H_
#define TOOLS_GN_ARGS_H_

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/synchronization/lock.h"
#include "tools/gn/err.h"
#include "tools/gn/scope.h"

extern const char kBuildArgs_Help[];

class Args {
 public:
  Args();
  Args(const Args& other);
  ~Args();

  
  
  void AddArgOverride(const char* name, const Value& value);
  void AddArgOverrides(const Scope::KeyValueMap& overrides);

  
  
  const Value* GetArgOverride(const char* name) const;

  
  Scope::KeyValueMap GetAllOverrides() const;

  
  
  
  void SetupRootScope(Scope* dest,
                      const Scope::KeyValueMap& toolchain_overrides) const;

  
  
  
  
  
  
  
  
  
  bool DeclareArgs(const Scope::KeyValueMap& args,
                   Scope* scope_to_set,
                   Err* err) const;

  
  
  bool VerifyAllOverridesUsed(Err* err) const;

  
  
  static bool VerifyAllOverridesUsed(
      const Scope::KeyValueMap& overrides,
      const Scope::KeyValueMap& declared_arguments,
      Err* err);

  
  
  
  void MergeDeclaredArguments(Scope::KeyValueMap* dest) const;

 private:
  
  void SetSystemVarsLocked(Scope* scope) const;

  
  void ApplyOverridesLocked(const Scope::KeyValueMap& values,
                            Scope* scope) const;

  void SaveOverrideRecordLocked(const Scope::KeyValueMap& values) const;

  
  
  Scope::KeyValueMap overrides_;

  mutable base::Lock lock_;

  
  
  
  mutable Scope::KeyValueMap all_overrides_;

  
  
  mutable Scope::KeyValueMap declared_arguments_;

  Args& operator=(const Args& other);  
};

#endif  
