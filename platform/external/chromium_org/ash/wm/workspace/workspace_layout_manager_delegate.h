// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WORKSPACE_WORKSPACE_LAYOUT_MANAGER_DELEGATE_H_
#define ASH_WM_WORKSPACE_WORKSPACE_LAYOUT_MANAGER_DELEGATE_H_

#include "ash/wm/wm_types.h"

namespace aura {
class Window;
}

namespace ash {
namespace wm {
class WindowState;
}

class WorkspaceLayoutManagerDelegate {
 public:
  WorkspaceLayoutManagerDelegate() {}
  virtual ~WorkspaceLayoutManagerDelegate() {}

  
  virtual void OnWindowAddedToLayout(aura::Window* child) = 0;

  
  virtual void OnWindowRemovedFromLayout(aura::Window* child) = 0;

  
  virtual void OnChildWindowVisibilityChanged(aura::Window* child,
                                              bool visible) = 0;

  
  virtual void OnWindowStackingChanged(aura::Window* window) = 0;

  
  virtual void OnPostWindowStateTypeChange(wm::WindowState* window_state,
                                           wm::WindowStateType old_type) = 0;

  
  virtual void OnDisplayWorkAreaInsetsChanged() = 0;
};

}  

#endif  
