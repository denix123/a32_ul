// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_TRANSIENT_WINDOW_OBSERVER_H_
#define UI_WM_CORE_TRANSIENT_WINDOW_OBSERVER_H_

#include "ui/wm/wm_export.h"

namespace aura {
class Window;
}

namespace wm {

class WM_EXPORT TransientWindowObserver {
 public:
  
  virtual void OnTransientChildAdded(aura::Window* window,
                                     aura::Window* transient) = 0;

  
  virtual void OnTransientChildRemoved(aura::Window* window,
                                       aura::Window* transient) = 0;

 protected:
  virtual ~TransientWindowObserver() {}
};

}  

#endif  