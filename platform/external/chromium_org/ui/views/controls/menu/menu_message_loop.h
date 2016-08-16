// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_MESSAGE_LOOP_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_MESSAGE_LOOP_H_

#include "ui/gfx/native_widget_types.h"

namespace gfx {
class Point;
}

namespace ui {
class LocatedEvent;
}

namespace views {

class MenuController;
class Widget;

class MenuMessageLoop {
 public:
  virtual ~MenuMessageLoop() {}

  
  static MenuMessageLoop* Create();

  
  
  
  virtual void Run(MenuController*, Widget* owner, bool nested_menu) = 0;

  
  
  virtual bool ShouldQuitNow() const = 0;

  
  virtual void QuitNow() = 0;

  
  
  virtual void RepostEventToWindow(const ui::LocatedEvent& event,
                                   gfx::NativeWindow window,
                                   const gfx::Point& screen_loc) = 0;

  
  
  virtual void ClearOwner() = 0;
};

}  

#endif  
