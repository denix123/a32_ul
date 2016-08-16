// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_TOPLEVEL_WINDOW_EVENT_HANDLER_H_
#define ASH_WM_TOPLEVEL_WINDOW_EVENT_HANDLER_H_

#include <set>

#include "ash/ash_export.h"
#include "ash/display/display_controller.h"
#include "ash/wm/wm_types.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/event_handler.h"
#include "ui/gfx/point.h"
#include "ui/gfx/rect.h"
#include "ui/wm/public/window_move_client.h"

namespace aura {
class Window;
}

namespace ui {
class LocatedEvent;
}

namespace ash {

class WindowResizer;

class ASH_EXPORT ToplevelWindowEventHandler
    : public ui::EventHandler,
      public aura::client::WindowMoveClient,
      public DisplayController::Observer {
 public:
  ToplevelWindowEventHandler();
  virtual ~ToplevelWindowEventHandler();

  
  virtual void OnKeyEvent(ui::KeyEvent* event) OVERRIDE;
  virtual void OnMouseEvent(ui::MouseEvent* event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  virtual aura::client::WindowMoveResult RunMoveLoop(
      aura::Window* source,
      const gfx::Vector2d& drag_offset,
      aura::client::WindowMoveSource move_source) OVERRIDE;
  virtual void EndMoveLoop() OVERRIDE;

  
  virtual void OnDisplayConfigurationChanging() OVERRIDE;

 private:
  class ScopedWindowResizer;

  enum DragCompletionStatus {
    DRAG_COMPLETE,
    DRAG_REVERT,

    
    
    
    DRAG_RESIZER_WINDOW_DESTROYED
  };

  
  
  bool AttemptToStartDrag(aura::Window* window,
                          const gfx::Point& point_in_parent,
                          int window_component,
                          aura::client::WindowMoveSource source);

  
  
  bool CompleteDrag(DragCompletionStatus status);

  void HandleMousePressed(aura::Window* target, ui::MouseEvent* event);
  void HandleMouseReleased(aura::Window* target, ui::MouseEvent* event);

  
  void HandleDrag(aura::Window* target, ui::LocatedEvent* event);

  
  void HandleMouseMoved(aura::Window* target, ui::LocatedEvent* event);

  
  void HandleMouseExited(aura::Window* target, ui::LocatedEvent* event);

  
  
  void SetWindowStateTypeFromGesture(aura::Window* window,
                                    wm::WindowStateType new_state_type);

  
  void ResizerWindowDestroyed();

  
  
  int first_finger_hittest_;

  
  
  
  gfx::Rect pre_drag_window_bounds_;

  
  bool in_move_loop_;

  
  bool in_gesture_drag_;

  
  bool drag_reverted_;

  scoped_ptr<ScopedWindowResizer> window_resizer_;

  base::Closure quit_closure_;

  
  
  bool* destroyed_;

  DISALLOW_COPY_AND_ASSIGN(ToplevelWindowEventHandler);
};

}  

#endif  
