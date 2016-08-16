// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_APPLICATION_APPLICATION_RUNNER_CHROMIUM_H_
#define MOJO_APPLICATION_APPLICATION_RUNNER_CHROMIUM_H_

#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "mojo/public/cpp/system/core.h"

namespace mojo {

class ApplicationDelegate;

class ApplicationRunnerChromium {
 public:
  
  explicit ApplicationRunnerChromium(ApplicationDelegate* delegate);
  ~ApplicationRunnerChromium();

  void set_message_loop_type(base::MessageLoop::Type type);

  
  
  
  MojoResult Run(MojoHandle shell_handle);

 private:
  scoped_ptr<ApplicationDelegate> delegate_;

  
  
  base::MessageLoop::Type message_loop_type_;
  
  bool has_run_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(ApplicationRunnerChromium);
};

}  

#endif  
