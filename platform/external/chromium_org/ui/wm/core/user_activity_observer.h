// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_USER_ACTIVITY_OBSERVER_H_
#define UI_WM_CORE_USER_ACTIVITY_OBSERVER_H_

#include "base/basictypes.h"
#include "ui/wm/wm_export.h"

namespace ui {
class Event;
}

namespace wm {

class WM_EXPORT UserActivityObserver {
 public:
  
  
  
  virtual void OnUserActivity(const ui::Event* event) = 0;

 protected:
  UserActivityObserver() {}
  virtual ~UserActivityObserver() {}

  DISALLOW_COPY_AND_ASSIGN(UserActivityObserver);
};

}  

#endif  
