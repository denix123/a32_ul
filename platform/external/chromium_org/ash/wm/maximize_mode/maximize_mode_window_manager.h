// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_MAXIMIZE_MODE_MAXIMIZE_MODE_WINDOW_MANAGER_H_
#define ASH_WM_MAXIMIZE_MODE_MAXIMIZE_MODE_WINDOW_MANAGER_H_

#include <map>
#include <set>

#include "ash/ash_export.h"
#include "ash/shell_observer.h"
#include "ash/wm/window_state.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/aura/window_observer.h"
#include "ui/events/event_handler.h"
#include "ui/gfx/display_observer.h"

namespace ui {
class TouchEvent;
}

namespace ash {
class MaximizeModeController;
class MaximizeModeWindowState;

class ASH_EXPORT MaximizeModeWindowManager : public aura::WindowObserver,
                                             public gfx::DisplayObserver,
                                             public ShellObserver,
                                             public ui::EventHandler {
 public:
  
  virtual ~MaximizeModeWindowManager();

  
  int GetNumberOfManagedWindows();

  
  
  
  
  void AddWindow(aura::Window* window);

  
  void WindowStateDestroyed(aura::Window* window);

  
  virtual void OnOverviewModeStarting() OVERRIDE;
  virtual void OnOverviewModeEnding() OVERRIDE;

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;
  virtual void OnWindowAdded(aura::Window* window) OVERRIDE;
  virtual void OnWindowBoundsChanged(aura::Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void OnDisplayAdded(const gfx::Display& display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t metrics) OVERRIDE;

  
  virtual void OnTouchEvent(ui::TouchEvent* event) OVERRIDE;

 protected:
  friend class MaximizeModeController;

  
  MaximizeModeWindowManager();

 private:
  typedef std::map<aura::Window*, MaximizeModeWindowState*> WindowToState;

  
  void MaximizeAllWindows();

  
  void RestoreAllWindows();

  
  
  
  
  
  void MaximizeAndTrackWindow(aura::Window* window);

  
  void ForgetWindow(aura::Window* window);

  
  bool ShouldHandleWindow(aura::Window* window);

  
  void AddWindowCreationObservers();

  
  void RemoveWindowCreationObservers();

  
  
  void DisplayConfigurationChanged();

  
  bool IsContainerWindow(aura::Window* window);

  
  void EnableBackdropBehindTopWindowOnEachDisplay(bool enable);

  
  WindowToState window_state_map_;

  
  std::set<aura::Window*> observed_container_windows_;

  
  bool backdrops_hidden_;

  DISALLOW_COPY_AND_ASSIGN(MaximizeModeWindowManager);
};

}  

#endif  
