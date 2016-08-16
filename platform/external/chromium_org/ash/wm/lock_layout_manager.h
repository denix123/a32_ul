// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_LOCK_LAYOUT_MANAGER_H_
#define ASH_WM_LOCK_LAYOUT_MANAGER_H_

#include "ash/ash_export.h"
#include "ash/shell_delegate.h"
#include "ash/snap_to_pixel_layout_manager.h"
#include "ash/wm/wm_types.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/layout_manager.h"
#include "ui/aura/window_observer.h"
#include "ui/gfx/rect.h"
#include "ui/keyboard/keyboard_controller.h"
#include "ui/keyboard/keyboard_controller_observer.h"

namespace aura {
class RootWindow;
class Window;
}

namespace ui {
class Layer;
}

namespace ash {
namespace wm {
class WindowState;
class WMEvent;
}

class ASH_EXPORT LockLayoutManager
    : public SnapToPixelLayoutManager,
      public aura::WindowObserver,
      public VirtualKeyboardStateObserver,
      public keyboard::KeyboardControllerObserver {
 public:
  explicit LockLayoutManager(aura::Window* window);
  virtual ~LockLayoutManager();

  
  virtual void OnWindowResized() OVERRIDE;
  virtual void OnWindowAddedToLayout(aura::Window* child) OVERRIDE;
  virtual void OnWillRemoveWindowFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnWindowRemovedFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnChildWindowVisibilityChanged(aura::Window* child,
                                              bool visibile) OVERRIDE;
  virtual void SetChildBounds(aura::Window* child,
                              const gfx::Rect& requested_bounds) OVERRIDE;

  
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

  
  virtual void OnVirtualKeyboardStateChanged(bool activated) OVERRIDE;

  
  virtual void OnKeyboardBoundsChanging(const gfx::Rect& new_bounds) OVERRIDE;

 private:
  
  
  void AdjustWindowsForWorkAreaChange(const wm::WMEvent* event);

  aura::Window* window_;
  aura::Window* root_window_;

  
  bool is_observing_keyboard_;

  
  gfx::Rect keyboard_bounds_;

  DISALLOW_COPY_AND_ASSIGN(LockLayoutManager);
};

}  

#endif  
