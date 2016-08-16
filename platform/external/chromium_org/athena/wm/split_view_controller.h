// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_WM_SPLIT_VIEW_CONTROLLER_H_
#define ATHENA_WM_SPLIT_VIEW_CONTROLLER_H_

#include "athena/athena_export.h"
#include "athena/util/drag_handle.h"
#include "athena/wm/bezel_controller.h"
#include "athena/wm/public/window_manager_observer.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"

namespace gfx {
class Rect;
class Transform;
}

namespace aura {
class ScopedWindowTargeter;
class Window;
class WindowTargeter;
}

namespace views {
class ViewTargeterDelegate;
class Widget;
}

namespace athena {
class WindowListProvider;

class ATHENA_EXPORT SplitViewController
    : public BezelController::ScrollDelegate,
      public DragHandleScrollDelegate,
      public WindowManagerObserver {
 public:
  SplitViewController(aura::Window* container,
                      WindowListProvider* window_list_provider);

  virtual ~SplitViewController();

  bool CanActivateSplitViewMode() const;
  bool IsSplitViewModeActive() const;

  
  
  
  
  
  
  void ActivateSplitMode(aura::Window* left,
                         aura::Window* right,
                         aura::Window* to_activate);

  
  void DeactivateSplitMode();

  
  
  
  void ReplaceWindow(aura::Window* window,
                     aura::Window* replace_with);

  
  
  gfx::Rect GetLeftAreaBounds();
  gfx::Rect GetRightAreaBounds();

  aura::Window* left_window() { return left_window_; }
  aura::Window* right_window() { return right_window_; }

 private:
  enum State {
    
    
    INACTIVE,
    
    
    
    SCROLLING,
    
    
    ACTIVE
  };

  void SetState(State state);

  void InitializeDivider();
  void HideDivider();
  void ShowDivider();

  void UpdateLayout(bool animate);

  void SetWindowTransforms(const gfx::Transform& left_transform,
                           const gfx::Transform& right_transform,
                           const gfx::Transform& divider_transform,
                           bool animate);

  
  void OnAnimationCompleted();

  
  
  int GetDefaultDividerPosition();

  
  virtual void BezelScrollBegin(BezelController::Bezel bezel,
                                float delta) OVERRIDE;
  virtual void BezelScrollEnd() OVERRIDE;
  virtual void BezelScrollUpdate(float delta) OVERRIDE;
  virtual bool BezelCanScroll() OVERRIDE;

  
  virtual void HandleScrollBegin(float delta) OVERRIDE;
  virtual void HandleScrollEnd() OVERRIDE;
  virtual void HandleScrollUpdate(float delta) OVERRIDE;

  
  virtual void OnOverviewModeEnter() OVERRIDE;
  virtual void OnOverviewModeExit() OVERRIDE;
  virtual void OnSplitViewModeEnter() OVERRIDE;
  virtual void OnSplitViewModeExit() OVERRIDE;

  State state_;

  aura::Window* container_;

  
  WindowListProvider* window_list_provider_;

  
  
  aura::Window* left_window_;
  aura::Window* right_window_;

  
  
  int divider_position_;

  
  
  int divider_scroll_start_position_;

  
  views::Widget* divider_widget_;

  
  
  views::View* drag_handle_;

  scoped_ptr<aura::ScopedWindowTargeter> window_targeter_;
  scoped_ptr<views::ViewTargeterDelegate> view_targeter_delegate_;

  
  
  std::vector<aura::Window*> to_hide_;

  base::WeakPtrFactory<SplitViewController> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SplitViewController);
};

}  

#endif  
