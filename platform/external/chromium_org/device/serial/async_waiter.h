// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_SERIAL_ASYNC_WAITER_H_
#define DEVICE_SERIAL_ASYNC_WAITER_H_

#include "base/callback.h"
#include "mojo/public/c/environment/async_waiter.h"
#include "mojo/public/cpp/environment/environment.h"
#include "mojo/public/cpp/system/handle.h"

namespace device {

class AsyncWaiter {
 public:
  typedef base::Callback<void(MojoResult)> Callback;

  AsyncWaiter(mojo::Handle handle,
              MojoHandleSignals signals,
              const Callback& callback);
  ~AsyncWaiter();

 private:
  static void WaitComplete(void* waiter, MojoResult result);
  void WaitCompleteInternal(MojoResult result);

  const MojoAsyncWaiter* waiter_;
  MojoAsyncWaitID id_;
  const Callback callback_;

  DISALLOW_COPY_AND_ASSIGN(AsyncWaiter);
};

}  

#endif  
