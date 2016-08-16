// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_X11_MOVE_LOOP_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_X11_MOVE_LOOP_H_

#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/x/x11_types.h"

namespace views {

class X11MoveLoop {
 public:
  virtual ~X11MoveLoop() {}

  
  
  
  
  virtual bool RunMoveLoop(aura::Window* window, gfx::NativeCursor cursor) = 0;

  
  virtual void UpdateCursor(gfx::NativeCursor cursor) = 0;

  
  virtual void EndMoveLoop() = 0;
};

}  

#endif  
