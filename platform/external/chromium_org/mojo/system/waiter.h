// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_WAITER_H_
#define MOJO_SYSTEM_WAITER_H_

#include <stdint.h>

#include "base/macros.h"
#include "base/synchronization/condition_variable.h"
#include "base/synchronization/lock.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class MOJO_SYSTEM_IMPL_EXPORT Waiter {
 public:
  Waiter();
  ~Waiter();

  
  
  void Init();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  MojoResult Wait(MojoDeadline deadline, uint32_t* context);

  
  
  void Awake(MojoResult result, uint32_t context);

 private:
  base::ConditionVariable cv_;  
  base::Lock lock_;             
#ifndef NDEBUG
  bool initialized_;
#endif
  bool awoken_;
  MojoResult awake_result_;
  
  
  
  uint32_t awake_context_;

  DISALLOW_COPY_AND_ASSIGN(Waiter);
};

}  
}  

#endif  
