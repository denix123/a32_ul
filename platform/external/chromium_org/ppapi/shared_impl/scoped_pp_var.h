// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_SHARED_IMPL_SCOPED_PP_VAR_H_
#define PPAPI_SHARED_IMPL_SCOPED_PP_VAR_H_

#include <stdlib.h>

#include "base/macros.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/shared_impl/ppapi_shared_export.h"

namespace ppapi {

class PPAPI_SHARED_EXPORT ScopedPPVar {
 public:
  struct PassRef {};

  ScopedPPVar();

  
  explicit ScopedPPVar(const PP_Var& v);

  
  ScopedPPVar(const PassRef&, const PP_Var& v);

  
  ScopedPPVar(const ScopedPPVar& other);

  ~ScopedPPVar();

  ScopedPPVar& operator=(const PP_Var& r);
  ScopedPPVar& operator=(const ScopedPPVar& other) {
    return operator=(other.var_);
  }

  const PP_Var& get() const { return var_; }

  
  
  PP_Var Release();

 private:
  PP_Var var_;
};

class PPAPI_SHARED_EXPORT ScopedPPVarArray {
 public:
  struct PassPPBMemoryAllocatedArray {};

  
  
  
  ScopedPPVarArray(const PassPPBMemoryAllocatedArray&,
                   PP_Var* array,
                   size_t size);

  explicit ScopedPPVarArray(size_t size);
  ~ScopedPPVarArray();

  
  
  PP_Var* Release(const PassPPBMemoryAllocatedArray&);

  PP_Var* get() { return array_; }
  size_t size() { return size_; }

  
  void Set(size_t index, const ScopedPPVar& var);
  const PP_Var& operator[](size_t index) { return array_[index]; }

 private:
  
  DISALLOW_COPY_AND_ASSIGN(ScopedPPVarArray);

  PP_Var* array_;
  size_t size_;
};

}  

#endif  
