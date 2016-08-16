// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PANELS_X11_PANEL_RESIZER_H_
#define CHROME_BROWSER_UI_VIEWS_PANELS_X11_PANEL_RESIZER_H_

#include "ui/events/event_handler.h"
#include "ui/gfx/point.h"

namespace aura {
class Window;
}

class Panel;

class X11PanelResizer : public ui::EventHandler {
 public:
  X11PanelResizer(Panel* panel, aura::Window* window);
  virtual ~X11PanelResizer();

 private:
  enum ResizeState {
    NOT_RESIZING,

    
    RESIZE_CAN_START,

    
    
    RESIZE_IN_PROGRESS
  };

  
  void OnMousePressed(ui::MouseEvent* event);

  
  void OnMouseDragged(ui::MouseEvent* event);

  
  
  void StopResizing(ui::MouseEvent* event, bool canceled);

  
  virtual void OnMouseEvent(ui::MouseEvent* event) OVERRIDE;

  
  Panel* panel_;

  
  aura::Window* window_;

  ResizeState resize_state_;

  
  int resize_component_;

  
  gfx::Point initial_press_location_in_screen_;

  DISALLOW_COPY_AND_ASSIGN(X11PanelResizer);
};

#endif  
