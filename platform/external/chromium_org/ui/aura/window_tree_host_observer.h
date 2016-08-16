// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_WINDOW_TREE_HOST_OBSERVER_H_
#define UI_AURA_WINDOW_TREE_HOST_OBSERVER_H_

#include "ui/aura/aura_export.h"

namespace gfx {
class Point;
}

namespace aura {
class Window;
class WindowTreeHost;

class AURA_EXPORT WindowTreeHostObserver {
 public:
  
  virtual void OnHostResized(const WindowTreeHost* host) {}

  
  virtual void OnHostMoved(const WindowTreeHost* host,
                           const gfx::Point& new_origin) {}

  
  virtual void OnHostCloseRequested(const WindowTreeHost* host) {}

 protected:
  virtual ~WindowTreeHostObserver() {}
};

}  

#endif  
