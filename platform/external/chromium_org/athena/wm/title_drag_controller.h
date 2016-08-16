// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_WM_TITLE_DRAG_CONTROLLER_H_
#define ATHENA_WM_TITLE_DRAG_CONTROLLER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "ui/aura/window_tracker.h"
#include "ui/events/event_handler.h"
#include "ui/gfx/geometry/point.h"

namespace aura {
class Window;
}

namespace wm {
class Shadow;
}

namespace athena {

class TitleDragControllerDelegate {
 public:
  virtual ~TitleDragControllerDelegate() {}

  
  
  virtual aura::Window* GetWindowBehind(aura::Window* window) = 0;

  
  virtual void OnTitleDragStarted(aura::Window* window) = 0;
  virtual void OnTitleDragCompleted(aura::Window* window) = 0;
  virtual void OnTitleDragCanceled(aura::Window* window) = 0;
};

class TitleDragController : public ui::EventHandler {
 public:
  TitleDragController(aura::Window* container,
                      TitleDragControllerDelegate* delegate);
  virtual ~TitleDragController();

 private:
  void EndTransition(aura::Window* window, bool complete);
  void OnTransitionEnd(aura::Window* window, bool complete);

  
  virtual void OnGestureEvent(ui::GestureEvent* gesture) OVERRIDE;

  aura::Window* container_;
  TitleDragControllerDelegate* delegate_;
  gfx::Point drag_start_location_;
  scoped_ptr<wm::Shadow> shadow_;
  aura::WindowTracker tracker_;

  base::WeakPtrFactory<TitleDragController> weak_ptr_;

  DISALLOW_COPY_AND_ASSIGN(TitleDragController);
};

}  

#endif  
