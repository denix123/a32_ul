// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_CHILD_PROCESS_H_
#define MOJO_SHELL_CHILD_PROCESS_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/embedder/scoped_platform_handle.h"

namespace base {
class CommandLine;
}

namespace mojo {
namespace shell {

class ChildProcess {
 public:
  enum Type {
    TYPE_TEST,
    
    TYPE_APP
  };

  virtual ~ChildProcess();

  
  
  
  static scoped_ptr<ChildProcess> Create(const base::CommandLine& command_line);

  
  
  virtual void Main() = 0;

 protected:
  ChildProcess();

  embedder::ScopedPlatformHandle* platform_channel() {
    return &platform_channel_;
  }

 private:
  
  embedder::ScopedPlatformHandle platform_channel_;

  DISALLOW_COPY_AND_ASSIGN(ChildProcess);
};

}  
}  

#endif  
