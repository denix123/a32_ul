// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_APPLICATION_APPLICATION_RUNNER_H_
#define MOJO_PUBLIC_APPLICATION_APPLICATION_RUNNER_H_

#include "mojo/public/cpp/system/core.h"

namespace mojo {

class ApplicationDelegate;

class ApplicationRunner {
 public:
  
  explicit ApplicationRunner(ApplicationDelegate* delegate);
  ~ApplicationRunner();

  
  
  
  MojoResult Run(MojoHandle shell_handle);

 private:
  ApplicationDelegate* delegate_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(ApplicationRunner);
};

}  

#endif  
