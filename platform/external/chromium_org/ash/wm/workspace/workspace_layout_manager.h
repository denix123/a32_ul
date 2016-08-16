// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WORKSPACE_WORKSPACE_LAYOUT_MANAGER_H_
#define ASH_WM_WORKSPACE_WORKSPACE_LAYOUT_MANAGER_H_

#include <set>

#include "ash/ash_export.h"
#include "ash/shell_observer.h"
#include "ash/wm/window_state_observer.h"
#include "ash/wm/wm_types.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/layout_manager.h"
#include "ui/aura/window_observer.h"
#include "ui/gfx/rect.h"
#include "ui/keyboard/keyboard_controller_observer.h"
#include "ui/wm/public/activation_change_observer.h"

namespace aura {
class RootWindow;
class Window;
}

namespace ui {
class Layer;
}

namespace ash {
class ShelfLayoutManager;
class WorkspaceLayoutManagerDelegate;

namespace wm {
class WindowState;
class WMEvent;
}

class ASH_EXPORT WorkspaceLayoutManager
    : public aura::LayoutManager,
      public aura::WindowObserver,
      public aura::client::ActivationChangeObserver,
      public keyboard::KeyboardControllerObserver,
      public ShellObserver,
      public wm::WindowStateObserver {
 public:
  explicit WorkspaceLayoutManager(aura::Window* window);
  virtual ~WorkspaceLayoutManager();

  void SetShelf(ShelfLayoutManager* shelf);

  
  
  
  void SetMaximizeBackdropDelegate(
      scoped_ptr<WorkspaceLayoutManagerDelegate> delegate);

  
  virtual void OnWindowResized() OVERRIDE {}
  virtual void OnWindowAddedToLayout(aura::Window* child) OVERRIDE;
  virtual void OnWillRemoveWindowFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnWindowRemovedFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnChildWindowVisibilityChanged(aura::Window* child,
                                              bool visibile) OVERRIDE;
  virtual void SetChildBounds(aura::Window* child,
                              const gfx::Rect& requested_bounds) OVERRIDE;

  
  virtual void OnDisplayWorkAreaInsetsChanged() OVERRIDE;

  
  virtual void OnWindowHierarchyChanged(
      const WindowObserver::HierarchyChangeParams& params) OVERRIDE;
  virtual void OnWindowPropertyChanged(aura::Window* window,
                                       const void* key,
                                       intptr_t old) OVERRIDE;
  virtual void OnWindowStackingChanged(aura::Window* window) OVERRIDE;
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;
  virtual void OnWindowBoundsChanged(aura::Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void OnWindowActivated(aura::Window* gained_active,
                                 aura::Window* lost_active) OVERRIDE;

  
  virtual void OnKeyboardBoundsChanging(const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void OnPostWindowStateTypeChange(
      wm::WindowState* window_state,
      wm::WindowStateType old_type) OVERRIDE;

 private:
  typedef std::set<aura::Window*> WindowSet;

  
  
  
  
  
  
  
  void AdjustAllWindowsBoundsForWorkAreaChange(const wm::WMEvent* event);

  
  void UpdateShelfVisibility();

  
  
  void UpdateFullscreenState();

  
  
  void UpdateBoundsFromStateType(wm::WindowState* window_state,
                                 wm::WindowStateType old_state_type);

  
  
  bool SetMaximizedOrFullscreenBounds(wm::WindowState* window_state);

  
  void SetChildBoundsAnimated(aura::Window* child, const gfx::Rect& bounds);

  ShelfLayoutManager* shelf_;
  aura::Window* window_;
  aura::Window* root_window_;

  
  WindowSet windows_;

  
  gfx::Rect work_area_in_parent_;

  
  bool is_fullscreen_;

  
  
  scoped_ptr<WorkspaceLayoutManagerDelegate> backdrop_delegate_;

  DISALLOW_COPY_AND_ASSIGN(WorkspaceLayoutManager);
};

}  

#endif  
