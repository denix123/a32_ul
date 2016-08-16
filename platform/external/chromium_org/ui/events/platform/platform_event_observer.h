// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_PLATFORM_PLATFORM_EVENT_OBSERVER_H_
#define UI_EVENTS_PLATFORM_PLATFORM_EVENT_OBSERVER_H_

#include "ui/events/events_export.h"
#include "ui/events/platform/platform_event_types.h"

namespace ui {

class EVENTS_EXPORT PlatformEventObserver {
 public:
  
  virtual void WillProcessEvent(const PlatformEvent& event) = 0;

  
  virtual void DidProcessEvent(const PlatformEvent& event) = 0;

 protected:
  virtual ~PlatformEventObserver() {}
};

}  

#endif  
