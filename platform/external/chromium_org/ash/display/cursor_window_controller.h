// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_CURSOR_WINDOW_CONTROLLER_H_
#define ASH_DISPLAY_CURSOR_WINDOW_CONTROLLER_H_

#include "ui/aura/window.h"
#include "ui/base/cursor/cursor.h"
#include "ui/gfx/display.h"

namespace ash {
namespace test {
class MirrorWindowTestApi;
}

class CursorWindowDelegate;

class CursorWindowController {
 public:
  CursorWindowController();
  ~CursorWindowController();

  bool is_cursor_compositing_enabled() const {
    return is_cursor_compositing_enabled_;
  }

  
  void SetCursorCompositingEnabled(bool enabled);

  
  void UpdateContainer();

  
  
  void SetDisplay(const gfx::Display& display);

  
  void UpdateLocation();
  void SetCursor(gfx::NativeCursor cursor);
  void SetCursorSet(ui::CursorSetType);
  void SetVisibility(bool visible);

 private:
  friend class test::MirrorWindowTestApi;

  
  
  void SetContainer(aura::Window* container);

  
  void SetBoundsInScreen(const gfx::Rect& bounds);

  
  void UpdateCursorImage();

  bool is_cursor_compositing_enabled_;
  aura::Window* container_;

  
  gfx::Rect bounds_in_screen_;

  
  int cursor_type_;

  ui::CursorSetType cursor_set_;
  gfx::Display::Rotation cursor_rotation_;
  gfx::Point hot_point_;

  
  
  gfx::Display display_;

  scoped_ptr<aura::Window> cursor_window_;
  scoped_ptr<CursorWindowDelegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(CursorWindowController);
};

}  

#endif  
