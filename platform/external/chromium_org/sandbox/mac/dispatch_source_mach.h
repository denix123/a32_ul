// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_MAC_DISPATCH_SOURCE_MACH_H_
#define SANDBOX_MAC_DISPATCH_SOURCE_MACH_H_

#include <dispatch/dispatch.h>

#include "base/basictypes.h"
#include "sandbox/sandbox_export.h"

namespace sandbox {

class SANDBOX_EXPORT DispatchSourceMach {
 public:
  
  
  
  DispatchSourceMach(const char* name,
                     mach_port_t port,
                     void (^event_handler)());

  
  
  DispatchSourceMach(dispatch_queue_t queue,
                     mach_port_t port,
                     void (^event_handler)());

  
  
  ~DispatchSourceMach();

  
  
  void Resume();

 private:
  
  
  void Cancel();

  
  dispatch_queue_t queue_;

  
  dispatch_source_t source_;

  
  dispatch_semaphore_t source_canceled_;

  DISALLOW_COPY_AND_ASSIGN(DispatchSourceMach);
};

}  

#endif  
