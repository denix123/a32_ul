// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SPY_SPY_H_
#define MOJO_SPY_SPY_H_

#include <string>
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class Thread;
}

namespace mojo {

class ApplicationManager;
class SpyServerImpl;

class Spy {
 public:
  Spy(mojo::ApplicationManager* application_manager,
      const std::string& options);
  ~Spy();

 private:
  scoped_refptr<SpyServerImpl> spy_server_;
  
  scoped_ptr<base::Thread> control_thread_;
};

}  

#endif  
