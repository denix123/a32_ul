// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MESSAGE_LOOP_MESSAGE_PUMP_DISPATCHER_H
#define BASE_MESSAGE_LOOP_MESSAGE_PUMP_DISPATCHER_H

#include <stdint.h>

#include "base/base_export.h"
#include "base/event_types.h"

namespace base {

class BASE_EXPORT MessagePumpDispatcher {
 public:
  enum PostDispatchAction {
    POST_DISPATCH_NONE = 0x0,
    POST_DISPATCH_QUIT_LOOP = 0x1,
    POST_DISPATCH_PERFORM_DEFAULT = 0x2,
  };

  virtual ~MessagePumpDispatcher() {}

  
  
  
  
  
  virtual uint32_t Dispatch(const NativeEvent& event) = 0;
};

}  

#endif  
