// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_C_ENVIRONMENT_ASYNC_WAITER_H_
#define MOJO_PUBLIC_C_ENVIRONMENT_ASYNC_WAITER_H_

#include "mojo/public/c/system/types.h"

typedef uintptr_t MojoAsyncWaitID;

typedef void (*MojoAsyncWaitCallback)(void* closure, MojoResult result);

struct MojoAsyncWaiter {
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  MojoAsyncWaitID (*AsyncWait)(MojoHandle handle,
                               MojoHandleSignals signals,
                               MojoDeadline deadline,
                               MojoAsyncWaitCallback callback,
                               void* closure);

  
  
  
  
  
  
  
  
  
  
  void (*CancelWait)(MojoAsyncWaitID wait_id);
};

#endif  
