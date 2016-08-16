// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_STATE_H_
#define ASH_WM_WINDOW_STATE_H_

#include "ash/ash_export.h"
#include "ash/wm/drag_details.h"
#include "ash/wm/wm_types.h"
#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "ui/aura/window_observer.h"
#include "ui/base/ui_base_types.h"

namespace aura {
class Window;
}

namespace gfx {
class Rect;
}

namespace ash {
class WorkspaceLayoutManager;
class LockWindowState;
class MaximizeModeWindowState;

namespace wm {
class WindowStateDelegate;
class WindowStateObserver;
class WMEvent;

class ASH_EXPORT WindowState : public aura::WindowObserver {
 public:

  
  
  
  
  class State {
   public:
    State() {}
    virtual ~State() {}

    
    virtual void OnWMEvent(WindowState* window_state, const WMEvent* event) = 0;

    virtual WindowStateType GetType() const = 0;

    
    
    
    
    
    virtual void AttachState(WindowState* window_state,
                             State* previous_state) = 0;

    
    
    
    virtual void DetachState(WindowState* window_state) = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(State);
  };

  
  virtual ~WindowState();

  aura::Window* window() { return window_; }
  const aura::Window* window() const { return window_; }

  bool HasDelegate() const;
  void SetDelegate(scoped_ptr<WindowStateDelegate> delegate);

  
  
  
  WindowStateType GetStateType() const;

  
  bool IsMinimized() const;
  bool IsMaximized() const;
  bool IsFullscreen() const;
  bool IsMaximizedOrFullscreen() const;
  bool IsSnapped() const;

  
  
  bool IsNormalStateType() const;

  bool IsNormalOrSnapped() const;

  bool IsActive() const;
  bool IsDocked() const;

  
  bool CanMaximize() const;
  bool CanMinimize() const;
  bool CanResize() const;
  bool CanSnap() const;
  bool CanActivate() const;

  
  bool HasRestoreBounds() const;

  
  
  
  void Maximize();
  void Minimize();
  void Unminimize();

  void Activate();
  void Deactivate();

  
  
  void Restore();

  
  
  void OnWMEvent(const WMEvent* event);

  
  
  

  
  void SaveCurrentBoundsForRestore();

  
  
  gfx::Rect GetRestoreBoundsInParent() const;

  
  
  
  gfx::Rect GetRestoreBoundsInScreen() const;

  
  
  void SetRestoreBoundsInParent(const gfx::Rect& bounds_in_parent);

  
  
  void SetRestoreBoundsInScreen(const gfx::Rect& bounds_in_screen);

  
  void ClearRestoreBounds();

  
  
  
  scoped_ptr<State> SetStateObject(scoped_ptr<State> new_state);

  
  
  
  bool unminimize_to_restore_bounds() const {
    return unminimize_to_restore_bounds_;
  }
  void set_unminimize_to_restore_bounds(bool value) {
    unminimize_to_restore_bounds_ = value;
  }

  
  
  bool hide_shelf_when_fullscreen() const {
    return hide_shelf_when_fullscreen_;
  }

  void set_hide_shelf_when_fullscreen(bool value) {
    hide_shelf_when_fullscreen_ = value;
  }

  
  
  
  
  
  bool minimum_visibility() const {
    return minimum_visibility_;
  }
  void set_minimum_visibility(bool minimum_visibility) {
    minimum_visibility_ = minimum_visibility;
  }

  
  bool can_be_dragged() const {
    return can_be_dragged_;
  }
  void set_can_be_dragged(bool can_be_dragged) {
    can_be_dragged_ = can_be_dragged;
  }

  
  
  const gfx::Rect* pre_auto_manage_window_bounds() const {
    return pre_auto_manage_window_bounds_.get();
  }
  void SetPreAutoManageWindowBounds(const gfx::Rect& bounds);

  

  void AddObserver(WindowStateObserver* observer);
  void RemoveObserver(WindowStateObserver* observer);

  
  bool is_dragged() const {
    return drag_details_;
  }

  
  
  bool window_position_managed() const { return window_position_managed_; }
  void set_window_position_managed(bool window_position_managed) {
    window_position_managed_ = window_position_managed;
  }

  
  bool bounds_changed_by_user() const { return bounds_changed_by_user_; }
  void set_bounds_changed_by_user(bool bounds_changed_by_user);

  
  bool panel_attached() const {
    return panel_attached_;
  }
  void set_panel_attached(bool panel_attached) {
    panel_attached_ = panel_attached;
  }

  
  
  bool ignored_by_shelf() const { return ignored_by_shelf_; }
  void set_ignored_by_shelf(bool ignored_by_shelf) {
    ignored_by_shelf_ = ignored_by_shelf;
  }

  
  
  
  bool can_consume_system_keys() const { return can_consume_system_keys_; }
  void set_can_consume_system_keys(bool can_consume_system_keys) {
    can_consume_system_keys_ = can_consume_system_keys;
  }

  
  
  bool top_row_keys_are_function_keys() const {
    return top_row_keys_are_function_keys_;
  }
  void set_top_row_keys_are_function_keys(bool value) {
    top_row_keys_are_function_keys_ = value;
  }

  
  
  
  
  bool in_immersive_fullscreen() const {
    return in_immersive_fullscreen_;
  }
  void set_in_immersive_fullscreen(bool enable) {
    in_immersive_fullscreen_ = enable;
  }

  
  
  void CreateDragDetails(aura::Window* window,
                         const gfx::Point& point_in_parent,
                         int window_component,
                         aura::client::WindowMoveSource source);

  
  
  void DeleteDragDetails();

  
  void SetAndClearRestoreBounds();

  
  const DragDetails* drag_details() const { return drag_details_.get(); }
  DragDetails* drag_details() { return drag_details_.get(); }

  
  virtual void OnWindowPropertyChanged(aura::Window* window,
                                       const void* key,
                                       intptr_t old) OVERRIDE;

 private:
  friend class DefaultState;
  friend class ash::LockWindowState;
  friend class ash::MaximizeModeWindowState;
  friend ASH_EXPORT WindowState* GetWindowState(aura::Window*);
  FRIEND_TEST_ALL_PREFIXES(WindowAnimationsTest, CrossFadeToBounds);

  explicit WindowState(aura::Window* window);

  WindowStateDelegate* delegate() { return delegate_.get(); }

  
  ui::WindowShowState GetShowState() const;

  
  void SetBoundsInScreen(const gfx::Rect& bounds_in_screen);

  
  
  void AdjustSnappedBounds(gfx::Rect* bounds);

  
  
  void UpdateWindowShowStateFromStateType();

  void NotifyPreStateTypeChange(WindowStateType old_window_state_type);
  void NotifyPostStateTypeChange(WindowStateType old_window_state_type);

  
  void SetBoundsDirect(const gfx::Rect& bounds);

  
  
  void SetBoundsConstrained(const gfx::Rect& bounds);

  
  
  void SetBoundsDirectAnimated(const gfx::Rect& bounds);

  
  
  void SetBoundsDirectCrossFade(const gfx::Rect& bounds);

  
  aura::Window* window_;
  scoped_ptr<WindowStateDelegate> delegate_;

  bool window_position_managed_;
  bool bounds_changed_by_user_;
  bool panel_attached_;
  bool ignored_by_shelf_;
  bool can_consume_system_keys_;
  bool top_row_keys_are_function_keys_;
  scoped_ptr<DragDetails> drag_details_;

  bool unminimize_to_restore_bounds_;
  bool in_immersive_fullscreen_;
  bool hide_shelf_when_fullscreen_;
  bool minimum_visibility_;
  bool can_be_dragged_;

  
  
  
  scoped_ptr<gfx::Rect> pre_auto_manage_window_bounds_;

  ObserverList<WindowStateObserver> observer_list_;

  
  
  bool ignore_property_change_;

  scoped_ptr<State> current_state_;

  DISALLOW_COPY_AND_ASSIGN(WindowState);
};

ASH_EXPORT WindowState* GetActiveWindowState();

ASH_EXPORT WindowState* GetWindowState(aura::Window* window);

ASH_EXPORT const WindowState*
GetWindowState(const aura::Window* window);

}  
}  

#endif  
