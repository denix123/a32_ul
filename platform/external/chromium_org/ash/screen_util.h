// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SCREEN_UTIL_H_
#define ASH_SCREEN_UTIL_H_

#include "ash/ash_export.h"
#include "base/basictypes.h"

namespace aura {
class Window;
}

namespace gfx {
class Display;
class Rect;
class Point;
}

namespace ash {

class ASH_EXPORT ScreenUtil {
 public:
  
  
  
  static gfx::Display FindDisplayContainingPoint(const gfx::Point& point);

  
  
  static gfx::Rect GetMaximizedWindowBoundsInParent(aura::Window* window);

  
  static gfx::Rect GetDisplayBoundsInParent(aura::Window* window);

  
  static gfx::Rect GetDisplayWorkAreaBoundsInParent(aura::Window* window);

  
  
  
  static gfx::Rect ConvertRectToScreen(aura::Window* window,
                                       const gfx::Rect& rect);

  
  
  static gfx::Rect ConvertRectFromScreen(aura::Window* window,
                                         const gfx::Rect& rect);

  
  
  static const gfx::Display& GetSecondaryDisplay();

  
  
  static const gfx::Display& GetDisplayForId(int64 display_id);

 private:
  ScreenUtil() {}
  ~ScreenUtil() {}

  DISALLOW_COPY_AND_ASSIGN(ScreenUtil);
};

}  

#endif  
