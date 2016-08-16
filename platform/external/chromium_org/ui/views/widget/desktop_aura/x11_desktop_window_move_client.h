// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_X11_DESKTOP_WINDOW_MOVE_CLIENT_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_X11_DESKTOP_WINDOW_MOVE_CLIENT_H_

#include <X11/Xlib.h>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/message_loop/message_loop.h"
#include "ui/gfx/point.h"
#include "ui/views/views_export.h"
#include "ui/views/widget/desktop_aura/x11_move_loop_delegate.h"
#include "ui/views/widget/desktop_aura/x11_whole_screen_move_loop.h"
#include "ui/wm/public/window_move_client.h"

namespace aura {
class WindowTreeHost;
}

namespace views {

class VIEWS_EXPORT X11DesktopWindowMoveClient :
      public views::X11MoveLoopDelegate,
      public aura::client::WindowMoveClient {
 public:
  X11DesktopWindowMoveClient();
  virtual ~X11DesktopWindowMoveClient();

  
  virtual void OnMouseMovement(XMotionEvent* event) OVERRIDE;
  virtual void OnMouseReleased() OVERRIDE;
  virtual void OnMoveLoopEnded() OVERRIDE;

  
  virtual aura::client::WindowMoveResult RunMoveLoop(
      aura::Window* window,
      const gfx::Vector2d& drag_offset,
      aura::client::WindowMoveSource move_source) OVERRIDE;
  virtual void EndMoveLoop() OVERRIDE;

 private:
  X11WholeScreenMoveLoop move_loop_;

  
  
  aura::WindowTreeHost* host_;

  
  
  
  gfx::Vector2d window_offset_;
};

}  

#endif  
