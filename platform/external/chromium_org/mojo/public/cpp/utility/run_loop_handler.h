// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_UTILITY_RUN_LOOP_HANDLER_H_
#define MOJO_PUBLIC_CPP_UTILITY_RUN_LOOP_HANDLER_H_

#include "mojo/public/cpp/system/core.h"

namespace mojo {

class RunLoopHandler {
 public:
  virtual void OnHandleReady(const Handle& handle) = 0;
  virtual void OnHandleError(const Handle& handle, MojoResult result) = 0;

 protected:
  virtual ~RunLoopHandler() {}
};

}  

#endif  
