// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_DOCK_DOCK_WINDOW_RESIZER_H_
#define ASH_WM_DOCK_DOCK_WINDOW_RESIZER_H_

#include "ash/wm/dock/dock_types.h"
#include "ash/wm/window_resizer.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"

namespace gfx {
class Point;
class Rect;
}

namespace aura {
class RootWindow;
}

namespace ash {
class DockedWindowLayoutManager;

class ASH_EXPORT DockedWindowResizer : public WindowResizer {
 public:
  virtual ~DockedWindowResizer();

  
  
  
  static DockedWindowResizer* Create(WindowResizer* next_window_resizer,
                                     wm::WindowState* window_state);

  
  virtual void Drag(const gfx::Point& location, int event_flags) OVERRIDE;
  virtual void CompleteDrag() OVERRIDE;
  virtual void RevertDrag() OVERRIDE;

 private:
  
  
  
  DockedWindowResizer(WindowResizer* next_window_resizer,
                      wm::WindowState* window_state);

  
  
  void MaybeSnapToEdge(const gfx::Rect& bounds, gfx::Point* offset);

  
  
  void StartedDragging();

  
  
  
  void FinishedDragging(aura::client::WindowMoveResult move_result);

  
  
  
  
  
  
  DockedAction MaybeReparentWindowOnDragCompletion(bool is_resized,
                                                   bool is_attached_panel);

  gfx::Point last_location_;

  
  scoped_ptr<WindowResizer> next_window_resizer_;

  
  DockedWindowLayoutManager* dock_layout_;
  DockedWindowLayoutManager* initial_dock_layout_;

  
  bool did_move_or_resize_;

  
  bool was_docked_;

  
  bool is_docked_;

  
  
  bool was_bounds_changed_by_user_;

  base::WeakPtrFactory<DockedWindowResizer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DockedWindowResizer);
};

}  

#endif  
