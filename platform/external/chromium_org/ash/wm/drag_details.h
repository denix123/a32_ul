// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_DRAG_DETAILS_H_
#define ASH_WM_DRAG_DETAILS_H_

#include "ash/ash_export.h"
#include "ash/wm/wm_types.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/rect.h"
#include "ui/wm/public/window_move_client.h"

namespace aura {
class Window;
}

namespace ash {

namespace wm {
class WindowState;
}

struct ASH_EXPORT DragDetails {
  DragDetails(aura::Window* window,
              const gfx::Point& location,
              int window_component,
              aura::client::WindowMoveSource source);
  ~DragDetails();

  ash::wm::WindowStateType initial_state_type;

  
  const gfx::Rect initial_bounds_in_parent;

  
  
  gfx::Rect restore_bounds;

  
  const gfx::Point initial_location_in_parent;

  
  const float initial_opacity;

  
  const int window_component;

  
  const int bounds_change;

  
  const int position_change_direction;

  
  const int size_change_direction;

  
  const bool is_resizable;

  
  const aura::client::WindowMoveSource source;

  
  bool should_attach_to_shelf;
};

}  

#endif  
