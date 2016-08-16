// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_PANELS_PANEL_LAYOUT_MANAGER_H_
#define ASH_WM_PANELS_PANEL_LAYOUT_MANAGER_H_

#include <list>

#include "ash/ash_export.h"
#include "ash/display/display_controller.h"
#include "ash/shelf/shelf_icon_observer.h"
#include "ash/shelf/shelf_layout_manager_observer.h"
#include "ash/shell_observer.h"
#include "ash/wm/window_state_observer.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "ui/aura/layout_manager.h"
#include "ui/aura/window_observer.h"
#include "ui/keyboard/keyboard_controller.h"
#include "ui/keyboard/keyboard_controller_observer.h"
#include "ui/wm/public/activation_change_observer.h"

namespace aura {
class Window;
class WindowTracker;
}

namespace gfx {
class Rect;
}

namespace views {
class Widget;
}

namespace ash {
class PanelCalloutWidget;
class Shelf;
class ShelfLayoutManager;


class ASH_EXPORT PanelLayoutManager
    : public aura::LayoutManager,
      public ShelfIconObserver,
      public ShellObserver,
      public aura::WindowObserver,
      public wm::WindowStateObserver,
      public aura::client::ActivationChangeObserver,
      public keyboard::KeyboardControllerObserver,
      public DisplayController::Observer,
      public ShelfLayoutManagerObserver {
 public:
  explicit PanelLayoutManager(aura::Window* panel_container);
  virtual ~PanelLayoutManager();

  
  void Shutdown();

  void StartDragging(aura::Window* panel);
  void FinishDragging();

  void ToggleMinimize(aura::Window* panel);

  
  void SetShowCalloutWidgets(bool show);

  
  views::Widget* GetCalloutWidgetForPanel(aura::Window* panel);

  Shelf* shelf() { return shelf_; }
  void SetShelf(Shelf* shelf);

  
  virtual void OnWindowResized() OVERRIDE;
  virtual void OnWindowAddedToLayout(aura::Window* child) OVERRIDE;
  virtual void OnWillRemoveWindowFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnWindowRemovedFromLayout(aura::Window* child) OVERRIDE;
  virtual void OnChildWindowVisibilityChanged(aura::Window* child,
                                              bool visibile) OVERRIDE;
  virtual void SetChildBounds(aura::Window* child,
                              const gfx::Rect& requested_bounds) OVERRIDE;

  
  virtual void OnShelfIconPositionsChanged() OVERRIDE;

  
  virtual void OnShelfAlignmentChanged(aura::Window* root_window) OVERRIDE;

  
  virtual void OnWindowPropertyChanged(aura::Window* window,
                                       const void* key,
                                       intptr_t old) OVERRIDE;

  
  virtual void OnPostWindowStateTypeChange(
      wm::WindowState* window_state,
      wm::WindowStateType old_type) OVERRIDE;

  
  virtual void OnWindowActivated(aura::Window* gained_active,
                                 aura::Window* lost_active) OVERRIDE;

  
  virtual void OnDisplayConfigurationChanged() OVERRIDE;

  
  virtual void WillChangeVisibilityState(
      ShelfVisibilityState new_state) OVERRIDE;

 private:
  friend class PanelLayoutManagerTest;
  friend class PanelWindowResizerTest;
  friend class DockedWindowResizerTest;
  friend class DockedWindowLayoutManagerTest;
  friend class WorkspaceControllerTest;

  views::Widget* CreateCalloutWidget();

  struct PanelInfo{
    PanelInfo() : window(NULL), callout_widget(NULL), slide_in(false) {}

    bool operator==(const aura::Window* other_window) const {
      return window == other_window;
    }

    
    aura::Window* window;
    
    
    
    PanelCalloutWidget* callout_widget;

    
    
    
    bool slide_in;
  };

  typedef std::list<PanelInfo> PanelList;

  void MinimizePanel(aura::Window* panel);
  void RestorePanel(aura::Window* panel);

  
  void Relayout();

  
  
  void UpdateStacking(aura::Window* active_panel);

  
  void UpdateCallouts();

  
  virtual void OnKeyboardBoundsChanging(
      const gfx::Rect& keyboard_bounds) OVERRIDE;

  
  aura::Window* panel_container_;
  
  bool in_add_window_;
  
  bool in_layout_;
  
  bool show_callout_widgets_;
  
  PanelList panel_windows_;
  
  aura::Window* dragged_panel_;
  
  Shelf* shelf_;
  
  ShelfLayoutManager* shelf_layout_manager_;

  
  
  
  scoped_ptr<aura::WindowTracker> restore_windows_on_shelf_visible_;

  
  
  aura::Window* last_active_panel_;
  base::WeakPtrFactory<PanelLayoutManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PanelLayoutManager);
};

}  

#endif  
