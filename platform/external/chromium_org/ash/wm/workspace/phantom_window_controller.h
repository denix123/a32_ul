// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WORKSPACE_PHANTOM_WINDOW_CONTROLLER_H_
#define ASH_WM_WORKSPACE_PHANTOM_WINDOW_CONTROLLER_H_

#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/rect.h"

namespace aura {
class Window;
}

namespace views {
class Widget;
}

namespace ash {

class ASH_EXPORT PhantomWindowController {
 public:
  explicit PhantomWindowController(aura::Window* window);

  
  virtual ~PhantomWindowController();

  
  void Show(const gfx::Rect& bounds_in_screen);

 private:
  friend class PhantomWindowControllerTest;

  
  
  scoped_ptr<views::Widget> CreatePhantomWidget(
      aura::Window* root_window,
      const gfx::Rect& bounds_in_screen);

  
  aura::Window* window_;

  
  
  gfx::Rect target_bounds_in_screen_;

  
  scoped_ptr<views::Widget> phantom_widget_;

  DISALLOW_COPY_AND_ASSIGN(PhantomWindowController);
};

}  

#endif  
