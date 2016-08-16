// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_SHELF_WIDGET_H_
#define ASH_SHELF_SHELF_WIDGET_H_

#include "ash/ash_export.h"
#include "ash/shelf/background_animator.h"
#include "ash/shelf/shelf_layout_manager_observer.h"
#include "ash/shelf/shelf_types.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_observer.h"

namespace aura {
class Window;
}

namespace ash {
class FocusCycler;
class Shelf;
class ShelfLayoutManager;
class StatusAreaWidget;
class WorkspaceController;

class ASH_EXPORT ShelfWidget : public views::Widget,
                               public views::WidgetObserver,
                               public ShelfLayoutManagerObserver {
 public:
  ShelfWidget(aura::Window* shelf_container,
              aura::Window* status_container,
              WorkspaceController* workspace_controller);
  virtual ~ShelfWidget();

  
  
  
  static bool ShelfAlignmentAllowed();

  void SetAlignment(ShelfAlignment alignmnet);
  ShelfAlignment GetAlignment() const;

  
  void SetPaintsBackground(ShelfBackgroundType background_type,
                           BackgroundAnimatorChangeType change_type);
  ShelfBackgroundType GetBackgroundType() const;

  
  
  void HideShelfBehindBlackBar(bool hide, int animation_time_ms);
  bool IsShelfHiddenBehindBlackBar() const;

  
  void SetDimsShelf(bool dimming);
  bool GetDimsShelf() const;

  ShelfLayoutManager* shelf_layout_manager() { return shelf_layout_manager_; }
  Shelf* shelf() const { return shelf_.get(); }
  StatusAreaWidget* status_area_widget() const { return status_area_widget_; }

  void CreateShelf();

  
  void SetShelfVisibility(bool visible);
  bool IsShelfVisible() const;

  
  void SetFocusCycler(FocusCycler* focus_cycler);
  FocusCycler* GetFocusCycler();

  
  
  void WillActivateAsFallback() { activating_as_fallback_ = true; }

  aura::Window* window_container() { return window_container_; }

  
  void ShutdownStatusAreaWidget();

  
  void ForceUndimming(bool force);

  
  virtual void OnWidgetActivationChanged(
      views::Widget* widget, bool active) OVERRIDE;

  
  
  int GetDimmingAlphaForTest();

  
  
  gfx::Rect GetDimmerBoundsForTest();

  
  void DisableDimmingAnimationsForTest();

  
  virtual void WillDeleteShelf() OVERRIDE;

 private:
  class DelegateView;

  ShelfLayoutManager* shelf_layout_manager_;
  scoped_ptr<Shelf> shelf_;
  StatusAreaWidget* status_area_widget_;

  
  
  DelegateView* delegate_view_;
  BackgroundAnimator background_animator_;
  bool activating_as_fallback_;
  aura::Window* window_container_;
};

}  

#endif  
