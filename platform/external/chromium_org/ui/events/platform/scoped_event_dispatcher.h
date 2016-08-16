// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_PLATFORM_SCOPED_EVENT_DISPATCHER_H_
#define UI_EVENTS_PLATFORM_SCOPED_EVENT_DISPATCHER_H_

#include "base/auto_reset.h"
#include "base/basictypes.h"
#include "ui/events/events_export.h"

namespace ui {

class PlatformEventDispatcher;

class EVENTS_EXPORT ScopedEventDispatcher {
 public:
  ScopedEventDispatcher(PlatformEventDispatcher** scoped_dispatcher,
                        PlatformEventDispatcher* new_dispatcher);
  ~ScopedEventDispatcher();

  operator PlatformEventDispatcher*() const { return original_; }

 private:
  PlatformEventDispatcher* original_;
  base::AutoReset<PlatformEventDispatcher*> restore_;

  DISALLOW_COPY_AND_ASSIGN(ScopedEventDispatcher);
};

}  

#endif  
