// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_COMMON_HANDLE_WATCHER_H_
#define MOJO_COMMON_HANDLE_WATCHER_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/run_loop.h"
#include "mojo/common/mojo_common_export.h"
#include "mojo/public/cpp/system/core.h"

namespace base {
class Thread;
}

namespace mojo {
namespace common {
namespace test {
class HandleWatcherTest;
}

class MOJO_COMMON_EXPORT HandleWatcher {
 public:
  HandleWatcher();

  
  ~HandleWatcher();

  
  
  
  
  
  
  
  void Start(const Handle& handle,
             MojoHandleSignals handle_signals,
             MojoDeadline deadline,
             const base::Callback<void(MojoResult)>& callback);

  
  
  void Stop();

 private:
  class StateBase;
  class SameThreadWatchingState;
  class SecondaryThreadWatchingState;

  
  scoped_ptr<StateBase> state_;

  DISALLOW_COPY_AND_ASSIGN(HandleWatcher);
};

}  
}  

#endif  
