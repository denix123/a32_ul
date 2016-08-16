// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_RESIZER_H_
#define ASH_WM_WINDOW_RESIZER_H_

#include "ash/ash_export.h"
#include "ash/wm/drag_details.h"
#include "ash/wm/window_state.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/rect.h"
#include "ui/wm/public/window_move_client.h"

namespace aura {
class Window;
}

namespace ash {

class ASH_EXPORT WindowResizer {
 public:
  
  static const int kBoundsChange_None;
  static const int kBoundsChange_Repositions;
  static const int kBoundsChange_Resizes;

  
  static const int kBoundsChangeDirection_None;
  static const int kBoundsChangeDirection_Horizontal;
  static const int kBoundsChangeDirection_Vertical;

  WindowResizer();
  WindowResizer(wm::WindowState* window_state);
  virtual ~WindowResizer();

  
  static int GetBoundsChangeForWindowComponent(int component);

  
  static int GetPositionChangeDirectionForWindowComponent(int window_component);

  
  
  
  virtual void Drag(const gfx::Point& location, int event_flags) = 0;

  
  virtual void CompleteDrag() = 0;

  
  virtual void RevertDrag() = 0;

  
  aura::Window* GetTarget() const {
    return window_state_ ? window_state_->window() : NULL;
  }

  
  const gfx::Point& GetInitialLocation() const {
    return window_state_->drag_details()->initial_location_in_parent;
  }

  
  const DragDetails& details() const { return *window_state_->drag_details(); }

 protected:
  gfx::Rect CalculateBoundsForDrag(const gfx::Point& location);

  static bool IsBottomEdge(int component);

  
  wm::WindowState* window_state_;

 private:
  
  
  void AdjustDeltaForTouchResize(int* delta_x, int* delta_y);

  
  
  gfx::Point GetOriginForDrag(int delta_x, int delta_y);

  
  gfx::Size GetSizeForDrag(int* delta_x, int* delta_y);

  
  int GetWidthForDrag(int min_width, int* delta_x);

  
  int GetHeightForDrag(int min_height, int* delta_y);
};

ASH_EXPORT scoped_ptr<WindowResizer> CreateWindowResizer(
    aura::Window* window,
    const gfx::Point& point_in_parent,
    int window_component,
    aura::client::WindowMoveSource source);

}  

#endif  
