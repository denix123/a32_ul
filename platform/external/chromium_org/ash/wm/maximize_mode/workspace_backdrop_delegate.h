// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_MAXIMIZE_MODE_WORKSPACE_BACKDROP_DELEGATE_H_
#define ASH_WM_MAXIMIZE_MODE_WORKSPACE_BACKDROP_DELEGATE_H_

#include "ash/ash_export.h"
#include "ash/wm/workspace/workspace_layout_manager_delegate.h"
#include "base/compiler_specific.h"
#include "ui/aura/window_observer.h"

namespace aura {
class Window;
}

namespace ui {
class Layer;
}

namespace views {
class Widget;
}

namespace ash {

class ASH_EXPORT WorkspaceBackdropDelegate
    : public aura::WindowObserver,
      public NON_EXPORTED_BASE(WorkspaceLayoutManagerDelegate) {
 public:
  explicit WorkspaceBackdropDelegate(aura::Window* container);
  virtual ~WorkspaceBackdropDelegate();

  
  virtual void OnWindowBoundsChanged(aura::Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void OnWindowAddedToLayout(aura::Window* child) OVERRIDE;
  virtual void OnWindowRemovedFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnChildWindowVisibilityChanged(aura::Window* child,
                                              bool visible) OVERRIDE;
  virtual void OnWindowStackingChanged(aura::Window* window) OVERRIDE;
  virtual void OnPostWindowStateTypeChange(
      wm::WindowState* window_state,
      wm::WindowStateType old_type) OVERRIDE;
  virtual void OnDisplayWorkAreaInsetsChanged() OVERRIDE;

 private:
  
  void RestackBackdrop();

  
  aura::Window* GetCurrentTopWindow();

  
  void AdjustToContainerBounds();

  
  void Show();

  
  views::Widget* background_;

  
  aura::Window* container_;

  
  bool in_restacking_;

  DISALLOW_COPY_AND_ASSIGN(WorkspaceBackdropDelegate);
};

}  

#endif  
