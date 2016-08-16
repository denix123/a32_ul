// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_PANELS_PANEL_WINDOW_RESIZER_H_
#define ASH_WM_PANELS_PANEL_WINDOW_RESIZER_H_

#include "ash/wm/window_resizer.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"

namespace gfx {
class Rect;
class Point;
}

namespace ash {

class ASH_EXPORT PanelWindowResizer : public WindowResizer {
 public:
  virtual ~PanelWindowResizer();

  
  
  
  static PanelWindowResizer* Create(WindowResizer* next_window_resizer,
                                    wm::WindowState* window_state);

  
  virtual void Drag(const gfx::Point& location, int event_flags) OVERRIDE;
  virtual void CompleteDrag() OVERRIDE;
  virtual void RevertDrag() OVERRIDE;

 private:
  
  
  
  
  PanelWindowResizer(WindowResizer* next_window_resizer,
                     wm::WindowState* window_state);

  
  
  bool AttachToLauncher(const gfx::Rect& bounds, gfx::Point* offset);

  
  
  void StartedDragging();

  
  
  void FinishDragging();

  
  void UpdateLauncherPosition();

  
  gfx::Point last_location_;

  
  
  scoped_ptr<WindowResizer> next_window_resizer_;

  
  aura::Window* panel_container_;
  aura::Window* initial_panel_container_;

  
  bool did_move_or_resize_;

  
  const bool was_attached_;

  base::WeakPtrFactory<PanelWindowResizer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PanelWindowResizer);
};

}  

#endif  
