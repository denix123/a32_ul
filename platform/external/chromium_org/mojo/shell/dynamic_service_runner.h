// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_DYNAMIC_SERVICE_RUNNER_H_
#define MOJO_SHELL_DYNAMIC_SERVICE_RUNNER_H_

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/public/cpp/system/core.h"

namespace base {
class FilePath;
}

namespace mojo {
namespace shell {

class Context;

class DynamicServiceRunner {
 public:
  virtual ~DynamicServiceRunner() {}

  
  
  
  virtual void Start(const base::FilePath& app_path,
                     ScopedMessagePipeHandle service_handle,
                     const base::Closure& app_completed_callback) = 0;
};

class DynamicServiceRunnerFactory {
 public:
  virtual ~DynamicServiceRunnerFactory() {}
  virtual scoped_ptr<DynamicServiceRunner> Create(Context* context) = 0;
};

template <class DynamicServiceRunnerImpl>
class DynamicServiceRunnerFactoryImpl : public DynamicServiceRunnerFactory {
 public:
  DynamicServiceRunnerFactoryImpl() {}
  virtual ~DynamicServiceRunnerFactoryImpl() {}
  virtual scoped_ptr<DynamicServiceRunner> Create(Context* context) OVERRIDE {
    return scoped_ptr<DynamicServiceRunner>(
        new DynamicServiceRunnerImpl(context));
  }
};

}  
}  

#endif  
