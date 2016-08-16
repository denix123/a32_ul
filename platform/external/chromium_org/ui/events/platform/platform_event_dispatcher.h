// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_PLATFORM_PLATFORM_EVENT_DISPATCHER_H_
#define UI_EVENTS_PLATFORM_PLATFORM_EVENT_DISPATCHER_H_

#include "base/basictypes.h"
#include "ui/events/events_export.h"
#include "ui/events/platform/platform_event_types.h"

namespace ui {

enum PostDispatchAction {
  POST_DISPATCH_NONE = 0x0,
  POST_DISPATCH_PERFORM_DEFAULT = 0x1,
  POST_DISPATCH_STOP_PROPAGATION = 0x2,
};

class EVENTS_EXPORT PlatformEventDispatcher {
 public:
  
  virtual bool CanDispatchEvent(const PlatformEvent& event) = 0;

  
  
  
  
  
  
  virtual uint32_t DispatchEvent(const PlatformEvent& event) = 0;

 protected:
  virtual ~PlatformEventDispatcher() {}
};

}  

#endif  
