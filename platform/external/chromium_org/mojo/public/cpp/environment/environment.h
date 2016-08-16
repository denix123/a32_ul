// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_ENVIRONMENT_ENVIRONMENT_H_
#define MOJO_PUBLIC_CPP_ENVIRONMENT_ENVIRONMENT_H_

#include "mojo/public/cpp/system/macros.h"

struct MojoAsyncWaiter;
struct MojoLogger;

namespace mojo {

class Environment {
 public:
  Environment();
  
  
  Environment(const MojoAsyncWaiter* default_async_waiter,
              const MojoLogger* default_logger);
  ~Environment();

  static const MojoAsyncWaiter* GetDefaultAsyncWaiter();
  static const MojoLogger* GetDefaultLogger();

 private:
  MOJO_DISALLOW_COPY_AND_ASSIGN(Environment);
};

}  

#endif  
